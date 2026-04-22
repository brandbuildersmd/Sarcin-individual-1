# 📊 ANALIZĂ VÂNZĂRI MAGAZIN ONLINE - Program C

## 📌 Descriere

Program în limbajul C pentru analiza vânzărilor unui magazin online pe baza unui fișier CSV cu 100,000 de tranzacții. Programul răspunde la 5 întrebări cheie de business și oferă insight-uri valoroase pentru decizii de marketing și stocuri.

---

## 📁 Fișiere Incluse

- **sales_analysis.c** - Codul sursă complet în C
- **sales.csv** - Fișier de date cu 100,000 tranzacții
- **README.md** - Acest fișier (documentație)

---

## 🔧 Compilare și Rulare

### Compilare:
```bash
gcc -o sales_analysis sales_analysis.c -Wall
```

### Rulare:
```bash
./sales_analysis
```

Sau specificați un alt fișier CSV:
```bash
./sales_analysis custom_sales.csv
```

---

## 📊 Date de Intrare (CSV)

Fișierul `sales.csv` conține următoarele coloane:

| Coloană | Descriere | Exemplu |
|---------|-----------|---------|
| **sale_date** | Data vânzării | 2016-11-10 |
| **product_id** | ID unic produs | 1860458 |
| **product_name** | Nume produs | inside |
| **product_category** | Categorie | role |
| **product_subcategory** | Subcategorie | some |
| **unit_price** | Preț unitar | 499.52 |
| **quantity_sold** | Cantitate vândută | 79 |
| **sale_country** | Țara | Brazil |
| **sale_city** | Orașul | New Jasonfurt |

**Total tranzacții:** 100,000  
**Perioada:** 1974 - 2024  
**Format dată:** YYYY-MM-DD

---

## 🎯 Cele 5 Întrebări de Business

### ✅ Întrebarea 1: Venit Total Lunar

**Scopul:** Identificarea lunilor cu cele mai mari venituri pentru planificare marketing și stocuri.

**Implementare:**
- Selectează automat anul cu cele mai multe tranzacții
- Calculează venit total pentru fiecare lună
- Afișează număr de tranzacții pe lună

**Output:**
```
┌─────────────────┬──────────────────┬─────────────────┐
│      Luna       │   Venit Total    │   Tranzacții    │
├─────────────────┼──────────────────┼─────────────────┤
│ Ianuarie        │    $1,234,567.89 │            150  │
│ Februarie       │    $2,345,678.90 │            180  │
...
```

**Insight:** Permite identificarea sezonalității și planificarea campaniilor.

---

### ✅ Întrebarea 2: Top 5 Produse

**Scopul:** Identificarea produselor best-seller pentru focus în marketing și stocuri.

**Implementare:**
- Agregează toate tranzacțiile pe produs
- Calculează venit total per produs
- Sortează descrescător și extrage top 5

**Output:**
```
┌──────┬────────────────────┬──────────────────┬─────────────┐
│ Rang │   Nume Produs      │  Venit Total     │  Cantitate  │
├──────┼────────────────────┼──────────────────┼─────────────┤
│  1   │ Product Alpha      │  $5,678,901.23   │      15,234 │
│  2   │ Product Beta       │  $4,567,890.12   │      12,456 │
...
```

**Insight:** Focus pe top produse = 80% din venituri (regula Pareto).

---

### ✅ Întrebarea 3: Distribuție Categorii

**Scopul:** Înțelegerea performanței fiecărei categorii de produse.

**Implementare:**
- Agregează venituri pe categorie
- Calculează procente din total
- Sortează descrescător după venit

**Output:**
```
┌────────────────────┬──────────────────┬──────────┬─────────────┐
│    Categorie       │   Venit Total    │    %     │ Tranzacții  │
├────────────────────┼──────────────────┼──────────┼─────────────┤
│ Electronics        │  $12,345,678.90  │   35.2%  │      25,000 │
│ Clothing           │   $8,234,567.89  │   23.4%  │      18,500 │
...
```

**Insight:** Alocarea bugetului marketing proporțional cu performanța categoriilor.

---

### ✅ Întrebarea 4: Top Orașe pe Țară

**Scopul:** Identificarea orașelor cu cele mai mari vânzări pentru optimizare logistică.

**Implementare:**
- Agregează venituri pe oraș și țară
- Sortează pe țară, apoi pe venit descrescător
- Afișează orașul #1 din fiecare țară

**Output:**
```
┌───────────────────────┬───────────────────┬──────────────────┐
│        Țara           │      Orașul       │   Venit Total    │
├───────────────────────┼───────────────────┼──────────────────┤
│ Brazil                │ São Paulo         │  $1,234,567.89   │
│ Canada                │ Toronto           │    $987,654.32   │
...
```

**Insight:** Unde să deschizi depozite și centre de distribuție.

---

### ✅ Întrebarea 5: Tendințe Subcategorii

**Scopul:** Identificarea subcategoriilor cu potențial de creștere.

**Implementare:**
- Agregează venituri pe subcategorie
- Identifică top 5 subcategorii
- Notă: Analiza lunară detaliată se face mai bine în Excel

**Output:**
```
Top 5 subcategorii după venit total:

1. Electronics Accessories - $5,678,901.23
2. Men's Apparel - $4,567,890.12
3. Home Decor - $3,456,789.01
4. Sports Equipment - $2,345,678.90
5. Kitchen Appliances - $1,234,567.89
```

**Insight:** Subcategorii pe care să investești pentru extindere.

---

## 🎮 Utilizare Interactivă

### Meniu Principal:

```
╔══════════════════════════════════════════════════════════╗
║        ANALIZĂ VÂNZĂRI MAGAZIN ONLINE                    ║
╚══════════════════════════════════════════════════════════╝
  1. Venit total lunar (Întrebarea 1)
  2. Top 5 produse (Întrebarea 2)
  3. Distribuție categorii (Întrebarea 3)
  4. Top orașe pe țară (Întrebarea 4)
  5. Tendințe subcategorii (Întrebarea 5)
  6. TOATE analizele
  7. Ieșire
──────────────────────────────────────────────────────────
  Alegeți opțiunea:
```

### Flux de Lucru Recomandat:

1. **Rulați opțiunea 6** pentru analiza completă
2. Exportați rezultatele (copy-paste din terminal)
3. Folosiți insight-urile pentru decizii de business

---

## 💻 Detalii Tehnice

### Structuri de Date:

```c
// Tranzacție individuală
typedef struct {
    char data[20];
    int product_id;
    char product_name[256];
    char category[256];
    char subcategory[256];
    float unit_price;
    int quantity_sold;
    char country[256];
    char city[256];
    float revenue;      // Calculat automat
    int month;          // Extras din dată
    int year;           // Extras din dată
} Transaction;
```

### Algoritmi Utilizați:

1. **Parsare CSV** - Citire și parsare linie cu linie
2. **Agregare** - Grupare după produs/categorie/oraș
3. **Sortare** - qsort() pentru top-uri
4. **Calculare procente** - Pentru distribuții

### Complexitate:

- **Încărcare date:** O(n) - 100,000 linii
- **Agregare:** O(n*m) unde m = număr produse/categorii unice
- **Sortare:** O(n log n)

### Memoria:

- **Maximă:** ~50MB pentru 100,000 tranzacții
- **Alocare dinamică** pentru flexibilitate

---

## 📈 Interpretare Rezultate

### Pentru Management:

**Întrebarea 1 + 2:**
- Identifică lunile de vârf → planifică campanii
- Focus pe top 5 produse → 80% din profit

**Întrebarea 3:**
- Distribuția categoriilor → alocare buget marketing
- Categorii slabe → oportunități de îmbunătățire

### Pentru Marketing:

**Întrebarea 2 + 5:**
- Top produse → feature în campanii
- Subcategorii trending → expansiune gamă produse

**Întrebarea 1:**
- Sezonalitate → timing promoții și reduceri

### Pentru Operațiuni/Logistică:

**Întrebarea 4:**
- Top orașe → locații depozite
- Concentrare geografică → optimizare transport

**Întrebarea 2:**
- Top produse → never out of stock
- Forecast cerere pe categorii

---

## 🚀 Extensii Posibile

### În C:
```c
// Adăugați funcții pentru:
- Export rezultate în CSV
- Grafice ASCII în terminal
- Filtrare pe perioadă specificată
- Analiză corelații (produs + oraș)
- Predicții trend folosind regresie liniară
```

### Integrare cu alte tool-uri:
```bash
# Export pentru Excel
./sales_analysis > results.txt

# Procesare cu Python/R pentru grafice
python visualize.py results.txt
```

---

## ⚠️ Limitări Curente

1. **Vizualizare:** Text-only, fără grafice
2. **Export:** Manual (copy-paste din terminal)
3. **Filtre:** Analizează tot dataset-ul, nu permite filtrare interactivă
4. **Performanță:** Pentru >1M tranzacții, considerați bază de date

**Soluție:** Pentru analiza vizuală avansată, folosiți Excel sau Python cu matplotlib.

---

## 🐛 Debugging

### Probleme Comune:

**1. Fișierul nu se găsește:**
```bash
# Verificați că sales.csv este în același folder
ls -la sales.csv
./sales_analysis
```

**2. Erori de alocare memorie:**
```bash
# Măriți constantele în cod
#define MAX_PRODUCTS 200000  // pentru mai multe produse
```

**3. Date corupte:**
```bash
# Verificați formatare CSV
head -5 sales.csv
```

---

## 📊 Statistici Dataset

- **Total tranzacții:** 100,000
- **Produse unice:** ~50,000
- **Categorii unice:** ~30-50
- **Țări:** ~150
- **Orașe:** ~500+
- **Perioadă:** 1974-2024 (50 ani)
- **Venit total:** ~$50+ milioane

---

## 🎓 Concepte Învățate

### Programare C:
- Alocare dinamică (malloc/free)
- Structuri de date complexe
- Parsare fișiere CSV
- Algoritmi de sortare (qsort)
- Agregare și calculare statistici

### Analiza Datelor:
- KPIs (Key Performance Indicators)
- Distribuții și procente
- Top-N queries
- Trend analysis
- Segmentare geografică

### Business Intelligence:
- Revenue analysis
- Product performance
- Category distribution
- Geographic insights
- Seasonality patterns

---

## 📝 TODO / Îmbunătățiri Viitoare

- [ ] Export rezultate în CSV/JSON
- [ ] Grafice ASCII în terminal
- [ ] Filtrare interactivă pe dată
- [ ] Analiză time-series (trend lunare)
- [ ] Comparație year-over-year
- [ ] Customer segmentation (dacă există customer_id)
- [ ] Corelații produs-oraș
- [ ] Predicții cu machine learning

---

## 🆘 Support

Pentru probleme sau întrebări:
1. Verificați secțiunea Debugging
2. Rulați cu flag-ul verbose (modificați codul)
3. Verificați formatare CSV

---

## 📄 Licență

Acest cod este furnizat ca material educațional pentru analiza datelor în C.

---

## 👨‍💻 Autor

Creat pentru analiza vânzărilor magazin online  
**Data:** Februarie 2026  
**Versiune:** 1.0

---

## 🎯 Concluzie

Acest program demonstrează cum poate fi folosit limbajul C pentru analiza datelor reale de business. Deși C nu este prima alegere pentru data analysis (Python/R fiind mai populare), oferă:

✅ **Performanță:** Foarte rapid pentru datasets mari  
✅ **Control:** Memorie și resurse complet controlate  
✅ **Portabilitate:** Rulează pe orice platformă  
✅ **Învățare:** Înțelegere profundă a algoritmilor  

Pentru proiecte de producție, considerați:
- **Python (pandas)** - pentru analiză rapidă și flexibilă
- **R** - pentru statistică avansată
- **SQL** - pentru query-uri complexe pe baze de date
- **Excel/Power BI** - pentru vizualizare business

Dar pentru **înțelegerea fundamentală** a procesării datelor, **C este perfect**! 🚀
