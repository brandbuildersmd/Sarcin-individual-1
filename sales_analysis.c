#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE 1024
#define MAX_PRODUCTS 100000
#define MAX_CATEGORIES 100
#define MAX_CITIES 1000
#define MAX_STR 256

// Structura pentru o tranzacție
typedef struct {
    char data[20];
    int product_id;
    char product_name[MAX_STR];
    char category[MAX_STR];
    char subcategory[MAX_STR];
    float unit_price;
    int quantity_sold;
    char country[MAX_STR];
    char city[MAX_STR];
    float revenue;
    int month;
    int year;
} Transaction;

// Structura pentru venituri lunare
typedef struct {
    int month;
    int year;
    float total_revenue;
    int count;
} MonthlyRevenue;

// Structura pentru produse top
typedef struct {
    char product_name[MAX_STR];
    char category[MAX_STR];
    float total_revenue;
    int total_quantity;
} ProductStats;

// Structura pentru categorii
typedef struct {
    char category[MAX_STR];
    float total_revenue;
    int count;
    float percentage;
} CategoryStats;

// Structura pentru orașe
typedef struct {
    char country[MAX_STR];
    char city[MAX_STR];
    float total_revenue;
    int count;
} CityStats;

// Structura pentru subcategorii lunare
typedef struct {
    char subcategory[MAX_STR];
    int month;
    float revenue;
} SubcategoryMonthly;

// Funcții
int loadTransactions(const char* filename, Transaction** transactions);
void parseDate(const char* date_str, int* year, int* month);
void analyzeMonthlyRevenue(Transaction* trans, int count);
void analyzeTopProducts(Transaction* trans, int count);
void analyzeCategoryDistribution(Transaction* trans, int count);
void analyzeTopCitiesByCountry(Transaction* trans, int count);
void analyzeSubcategoryTrends(Transaction* trans, int count);
void clearInputBuffer();
int compareProductsByRevenue(const void* a, const void* b);
int compareCitiesByRevenue(const void* a, const void* b);

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Parsare dată din format YYYY-MM-DD
void parseDate(const char* date_str, int* year, int* month) {
    sscanf(date_str, "%d-%d", year, month);
}

// Încărcarea tranzacțiilor din CSV
int loadTransactions(const char* filename, Transaction** transactions) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Eroare: Nu se poate deschide fișierul %s\n", filename);
        return 0;
    }
    
    char line[MAX_LINE];
    int count = 0;
    
    // Skip header
    fgets(line, MAX_LINE, file);
    
    // Alocare inițială
    *transactions = (Transaction*)malloc(MAX_PRODUCTS * sizeof(Transaction));
    if (*transactions == NULL) {
        printf("Eroare la alocarea memoriei!\n");
        fclose(file);
        return 0;
    }
    
    printf("Încărcare date din CSV...\n");
    
    while (fgets(line, MAX_LINE, file) && count < MAX_PRODUCTS) {
        Transaction* t = &(*transactions)[count];
        
        // Parse CSV line
        char* token;
        int field = 0;
        
        token = strtok(line, ",");
        while (token && field < 9) {
            switch(field) {
                case 0: // sale_date
                    strncpy(t->data, token, 19);
                    parseDate(token, &t->year, &t->month);
                    break;
                case 1: // product_id
                    t->product_id = atoi(token);
                    break;
                case 2: // product_name
                    strncpy(t->product_name, token, MAX_STR-1);
                    break;
                case 3: // category
                    strncpy(t->category, token, MAX_STR-1);
                    break;
                case 4: // subcategory
                    strncpy(t->subcategory, token, MAX_STR-1);
                    break;
                case 5: // unit_price
                    t->unit_price = atof(token);
                    break;
                case 6: // quantity_sold
                    t->quantity_sold = atoi(token);
                    break;
                case 7: // country
                    strncpy(t->country, token, MAX_STR-1);
                    break;
                case 8: // city
                    // Remove newline
                    token[strcspn(token, "\n")] = 0;
                    strncpy(t->city, token, MAX_STR-1);
                    break;
            }
            token = strtok(NULL, ",");
            field++;
        }
        
        // Calculare revenue
        t->revenue = t->unit_price * t->quantity_sold;
        
        count++;
        
        if (count % 10000 == 0) {
            printf("Procesate %d înregistrări...\n", count);
        }
    }
    
    fclose(file);
    printf("Total înregistrări încărcate: %d\n\n", count);
    
    return count;
}

// Comparator pentru sortare produse după revenue
int compareProductsByRevenue(const void* a, const void* b) {
    ProductStats* p1 = (ProductStats*)a;
    ProductStats* p2 = (ProductStats*)b;
    
    if (p2->total_revenue > p1->total_revenue) return 1;
    if (p2->total_revenue < p1->total_revenue) return -1;
    return 0;
}

// Comparator pentru sortare orașe
int compareCitiesByRevenue(const void* a, const void* b) {
    CityStats* c1 = (CityStats*)a;
    CityStats* c2 = (CityStats*)b;
    
    // Sortare după țară, apoi după revenue descrescător
    int cmp = strcmp(c1->country, c2->country);
    if (cmp != 0) return cmp;
    
    if (c2->total_revenue > c1->total_revenue) return 1;
    if (c2->total_revenue < c1->total_revenue) return -1;
    return 0;
}

// ÎNTREBAREA 1: Venit lunar
void analyzeMonthlyRevenue(Transaction* trans, int count) {
    printf("\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║  ÎNTREBAREA 1: VENIT TOTAL LUNAR                         ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    MonthlyRevenue monthly[12] = {0};
    
    // Inițializare luni
    for (int i = 0; i < 12; i++) {
        monthly[i].month = i + 1;
        monthly[i].total_revenue = 0;
        monthly[i].count = 0;
    }
    
    // Găsire an cu cele mai multe date
    int year_counts[100] = {0};
    int min_year = 3000, max_year = 0;
    
    for (int i = 0; i < count; i++) {
        if (trans[i].year < min_year) min_year = trans[i].year;
        if (trans[i].year > max_year) max_year = trans[i].year;
        
        int idx = trans[i].year - 1900;
        if (idx >= 0 && idx < 100) {
            year_counts[idx]++;
        }
    }
    
    int best_year = min_year;
    int max_count = 0;
    for (int i = 0; i < 100; i++) {
        if (year_counts[i] > max_count) {
            max_count = year_counts[i];
            best_year = 1900 + i;
        }
    }
    
    printf("Anul cu cele mai multe tranzacții: %d (%d tranzacții)\n\n", best_year, max_count);
    
    // Calculare venituri lunare pentru anul selectat
    for (int i = 0; i < count; i++) {
        if (trans[i].year == best_year && trans[i].month >= 1 && trans[i].month <= 12) {
            monthly[trans[i].month - 1].total_revenue += trans[i].revenue;
            monthly[trans[i].month - 1].count++;
        }
    }
    
    // Afișare rezultate
    const char* month_names[] = {
        "Ianuarie", "Februarie", "Martie", "Aprilie", "Mai", "Iunie",
        "Iulie", "August", "Septembrie", "Octombrie", "Noiembrie", "Decembrie"
    };
    
    printf("┌─────────────────┬──────────────────┬─────────────────┐\n");
    printf("│      Luna       │   Venit Total    │   Tranzacții    │\n");
    printf("├─────────────────┼──────────────────┼─────────────────┤\n");
    
    float total_revenue = 0;
    int total_transactions = 0;
    
    for (int i = 0; i < 12; i++) {
        printf("│ %-15s │ $%14.2f │ %15d │\n", 
               month_names[i], 
               monthly[i].total_revenue,
               monthly[i].count);
        total_revenue += monthly[i].total_revenue;
        total_transactions += monthly[i].count;
    }
    
    printf("├─────────────────┼──────────────────┼─────────────────┤\n");
    printf("│ TOTAL           │ $%14.2f │ %15d │\n", total_revenue, total_transactions);
    printf("└─────────────────┴──────────────────┴─────────────────┘\n");
}

// ÎNTREBAREA 2: Top 5 produse
void analyzeTopProducts(Transaction* trans, int count) {
    printf("\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║  ÎNTREBAREA 2: TOP 5 PRODUSE DUPĂ VENIT                  ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    ProductStats* products = (ProductStats*)malloc(MAX_PRODUCTS * sizeof(ProductStats));
    int product_count = 0;
    
    // Agregare produse
    for (int i = 0; i < count; i++) {
        int found = 0;
        for (int j = 0; j < product_count; j++) {
            if (strcmp(products[j].product_name, trans[i].product_name) == 0) {
                products[j].total_revenue += trans[i].revenue;
                products[j].total_quantity += trans[i].quantity_sold;
                found = 1;
                break;
            }
        }
        
        if (!found && product_count < MAX_PRODUCTS) {
            strncpy(products[product_count].product_name, trans[i].product_name, MAX_STR-1);
            strncpy(products[product_count].category, trans[i].category, MAX_STR-1);
            products[product_count].total_revenue = trans[i].revenue;
            products[product_count].total_quantity = trans[i].quantity_sold;
            product_count++;
        }
    }
    
    // Sortare
    qsort(products, product_count, sizeof(ProductStats), compareProductsByRevenue);
    
    // Afișare top 5
    printf("┌──────┬────────────────────┬──────────────────┬─────────────┐\n");
    printf("│ Rang │   Nume Produs      │  Venit Total     │  Cantitate  │\n");
    printf("├──────┼────────────────────┼──────────────────┼─────────────┤\n");
    
    for (int i = 0; i < 5 && i < product_count; i++) {
        printf("│  %d   │ %-18s │ $%14.2f │ %11d │\n",
               i + 1,
               products[i].product_name,
               products[i].total_revenue,
               products[i].total_quantity);
    }
    
    printf("└──────┴────────────────────┴──────────────────┴─────────────┘\n");
    
    free(products);
}

// ÎNTREBAREA 3: Distribuție categorii
void analyzeCategoryDistribution(Transaction* trans, int count) {
    printf("\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║  ÎNTREBAREA 3: DISTRIBUȚIE VÂNZĂRI PE CATEGORII          ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    CategoryStats categories[MAX_CATEGORIES];
    int cat_count = 0;
    
    // Agregare categorii
    for (int i = 0; i < count; i++) {
        int found = 0;
        for (int j = 0; j < cat_count; j++) {
            if (strcmp(categories[j].category, trans[i].category) == 0) {
                categories[j].total_revenue += trans[i].revenue;
                categories[j].count++;
                found = 1;
                break;
            }
        }
        
        if (!found && cat_count < MAX_CATEGORIES) {
            strncpy(categories[cat_count].category, trans[i].category, MAX_STR-1);
            categories[cat_count].total_revenue = trans[i].revenue;
            categories[cat_count].count = 1;
            cat_count++;
        }
    }
    
    // Calcul total pentru percentaje
    float grand_total = 0;
    for (int i = 0; i < cat_count; i++) {
        grand_total += categories[i].total_revenue;
    }
    
    for (int i = 0; i < cat_count; i++) {
        categories[i].percentage = (categories[i].total_revenue / grand_total) * 100.0;
    }
    
    // Sortare după revenue
    for (int i = 0; i < cat_count - 1; i++) {
        for (int j = 0; j < cat_count - i - 1; j++) {
            if (categories[j].total_revenue < categories[j + 1].total_revenue) {
                CategoryStats temp = categories[j];
                categories[j] = categories[j + 1];
                categories[j + 1] = temp;
            }
        }
    }
    
    // Afișare top 10 categorii
    printf("┌────────────────────┬──────────────────┬──────────┬─────────────┐\n");
    printf("│    Categorie       │   Venit Total    │    %%     │ Tranzacții  │\n");
    printf("├────────────────────┼──────────────────┼──────────┼─────────────┤\n");
    
    int limit = cat_count < 10 ? cat_count : 10;
    for (int i = 0; i < limit; i++) {
        printf("│ %-18s │ $%14.2f │ %7.2f%% │ %11d │\n",
               categories[i].category,
               categories[i].total_revenue,
               categories[i].percentage,
               categories[i].count);
    }
    
    printf("└────────────────────┴──────────────────┴──────────┴─────────────┘\n");
}

// ÎNTREBAREA 4: Top orașe pe țară
void analyzeTopCitiesByCountry(Transaction* trans, int count) {
    printf("\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║  ÎNTREBAREA 4: TOP ORAȘE PE FIECARE ȚARĂ                 ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    CityStats* cities = (CityStats*)malloc(MAX_CITIES * sizeof(CityStats));
    int city_count = 0;
    
    // Agregare orașe
    for (int i = 0; i < count; i++) {
        int found = 0;
        for (int j = 0; j < city_count; j++) {
            if (strcmp(cities[j].country, trans[i].country) == 0 &&
                strcmp(cities[j].city, trans[i].city) == 0) {
                cities[j].total_revenue += trans[i].revenue;
                cities[j].count++;
                found = 1;
                break;
            }
        }
        
        if (!found && city_count < MAX_CITIES) {
            strncpy(cities[city_count].country, trans[i].country, MAX_STR-1);
            strncpy(cities[city_count].city, trans[i].city, MAX_STR-1);
            cities[city_count].total_revenue = trans[i].revenue;
            cities[city_count].count = 1;
            city_count++;
        }
    }
    
    // Sortare
    qsort(cities, city_count, sizeof(CityStats), compareCitiesByRevenue);
    
    // Afișare top oraș pentru fiecare țară (primele 20 țări)
    printf("┌───────────────────────┬───────────────────┬──────────────────┐\n");
    printf("│        Țara           │      Orașul       │   Venit Total    │\n");
    printf("├───────────────────────┼───────────────────┼──────────────────┤\n");
    
    char last_country[MAX_STR] = "";
    int countries_shown = 0;
    
    for (int i = 0; i < city_count && countries_shown < 20; i++) {
        if (strcmp(cities[i].country, last_country) != 0) {
            printf("│ %-21s │ %-17s │ $%14.2f │\n",
                   cities[i].country,
                   cities[i].city,
                   cities[i].total_revenue);
            strncpy(last_country, cities[i].country, MAX_STR-1);
            countries_shown++;
        }
    }
    
    printf("└───────────────────────┴───────────────────┴──────────────────┘\n");
    
    free(cities);
}

// ÎNTREBAREA 5: Tendințe subcategorii
void analyzeSubcategoryTrends(Transaction* trans, int count) {
    printf("\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║  ÎNTREBAREA 5: TENDINȚE LUNARE SUBCATEGORII              ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    printf("Top 5 subcategorii după venit total:\n\n");
    
    // Găsire subcategorii top
    ProductStats subcats[MAX_CATEGORIES];
    int subcat_count = 0;
    
    for (int i = 0; i < count; i++) {
        int found = 0;
        for (int j = 0; j < subcat_count; j++) {
            if (strcmp(subcats[j].product_name, trans[i].subcategory) == 0) {
                subcats[j].total_revenue += trans[i].revenue;
                found = 1;
                break;
            }
        }
        
        if (!found && subcat_count < MAX_CATEGORIES) {
            strncpy(subcats[subcat_count].product_name, trans[i].subcategory, MAX_STR-1);
            subcats[subcat_count].total_revenue = trans[i].revenue;
            subcat_count++;
        }
    }
    
    // Sortare
    qsort(subcats, subcat_count, sizeof(ProductStats), compareProductsByRevenue);
    
    // Afișare top 5 subcategorii
    for (int i = 0; i < 5 && i < subcat_count; i++) {
        printf("%d. %s - $%.2f\n", i+1, subcats[i].product_name, subcats[i].total_revenue);
    }
    
    printf("\nNOTĂ: Pentru vizualizare completă a tendințelor lunare, folosiți Excel.\n");
}

// Meniu principal
void displayMenu() {
    printf("\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║        ANALIZĂ VÂNZĂRI MAGAZIN ONLINE                    ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    printf("  1. Venit total lunar (Întrebarea 1)\n");
    printf("  2. Top 5 produse (Întrebarea 2)\n");
    printf("  3. Distribuție categorii (Întrebarea 3)\n");
    printf("  4. Top orașe pe țară (Întrebarea 4)\n");
    printf("  5. Tendințe subcategorii (Întrebarea 5)\n");
    printf("  6. TOATE analizele\n");
    printf("  7. Ieșire\n");
    printf("──────────────────────────────────────────────────────────\n");
    printf("  Alegeți opțiunea: ");
}

int main(int argc, char* argv[]) {
    const char* filename = "sales.csv";
    
    // Verificare argument
    if (argc > 1) {
        filename = argv[1];
    }
    
    printf("\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║   SISTEM ANALIZĂ VÂNZĂRI - MAGAZIN ONLINE                ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    // Încărcare date
    Transaction* transactions = NULL;
    int trans_count = loadTransactions(filename, &transactions);
    
    if (trans_count == 0) {
        printf("Nu s-au putut încărca datele!\n");
        return 1;
    }
    
    int choice;
    int running = 1;
    
    while (running) {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                analyzeMonthlyRevenue(transactions, trans_count);
                break;
            case 2:
                analyzeTopProducts(transactions, trans_count);
                break;
            case 3:
                analyzeCategoryDistribution(transactions, trans_count);
                break;
            case 4:
                analyzeTopCitiesByCountry(transactions, trans_count);
                break;
            case 5:
                analyzeSubcategoryTrends(transactions, trans_count);
                break;
            case 6:
                analyzeMonthlyRevenue(transactions, trans_count);
                analyzeTopProducts(transactions, trans_count);
                analyzeCategoryDistribution(transactions, trans_count);
                analyzeTopCitiesByCountry(transactions, trans_count);
                analyzeSubcategoryTrends(transactions, trans_count);
                break;
            case 7:
                printf("\nLa revedere!\n");
                running = 0;
                break;
            default:
                printf("Opțiune invalidă!\n");
        }
        
        if (running && choice != 7) {
            printf("\nApăsați Enter pentru a continua...");
            clearInputBuffer();
            getchar();
        }
    }
    
    // Eliberare memorie
    free(transactions);
    
    return 0;
}
