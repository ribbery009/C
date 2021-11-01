#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void create_marks_csv(int *erzekeny, int *beteg, int *gyogyult, int feladat, int j)
{
    FILE *fp;

    char fn[7];
    snprintf(fn, 7, "Q%d.csv", feladat);
    fp = fopen(fn, "a+");
    if (j == 0)
    {
        fprintf(fp, "ID, Erzekeny, Beteg, Gyogyult");
    }
    fprintf(fp, "\n%d,%d,%d,%d", j + 1, erzekeny[9999], beteg[9999], gyogyult[9999]);
    fclose(fp);
    printf("\n file created");
}

int *RandomBetegGenerator(const int nMin, const int nMax, const int N)
{
    int i, j;
    static int beteg_lista[10];
    int db = 0;
    for (i = 0; i < N; i++)
    {
        beteg_lista[i] = rand() % (nMax - nMin) + nMin;

        if (i > 0)
        {
            db++;
            for (j = 0; j < db; j++)
            {
                //megnézem hogy volt e már a tömbben az adott szám, ha igen vissza megyek 1et a külső ciklus értékében (csökkentem i és db számok értékét 1-el)
                if (beteg_lista[j] == beteg_lista[i])
                {
                    i--;
                    db--;
                }
            }
        }
    }

    for (i = 0; i <= db; i++)
    {
        printf("beteg_lista: %d \n", beteg_lista[i]);
    }

    return beteg_lista;
}

int *BetegListaGenerator(int *sorszamok, const int N, const int erzekeny, const int beteg)
{
    int i, j, zs;
    static int populacio_lista[10000];

    int talalat;

    for (i = 0; i < N; i++)
    {
        talalat = 0;
        for (j = 0; j < 10; j++)
        {
            // ha i egyenlő a beteg lista adott sorszámával, akkor legyen i értéke beteg vagyis 1-es

            if (sorszamok[j] == i)
            {
                populacio_lista[i] = beteg;
                talalat = beteg;
            }
        }

        if (talalat == 1)
        {
        }
        else
        {
            populacio_lista[i] = erzekeny;
        }
    }

    // for (zs = 0; zs < N; zs++)
    // {
    //     printf("zs = %d populacio_lista: %d \n", zs, populacio_lista[zs]);
    // }

    return populacio_lista;
}

int *ElemiCiklus(int *populacio, const int erzekeny, const int beteg, const int gyogyult, const int nMin, const int nMax)
{

    int kapcsolo = 0, kapcsolo2 = 0;

    while (kapcsolo == 0)
    {
        int betegSorszam = rand() % (10000 - 1) + 1;

        if (populacio[betegSorszam] == 2)
        {
        }
        if (populacio[betegSorszam] == 1)
        {
            int vsz = rand() % (101 - 1) + 1;
            if (vsz < 80)
            {
                populacio[betegSorszam] = 2;
            }
            kapcsolo++;
        }

        if (populacio[betegSorszam] == 0)
        {

            int vsz = rand() % (101 - 1) + 1;
            int partnerSorszam;
            while (kapcsolo2 == 0)
            {
                partnerSorszam = rand() % (10000 - 1) + 1;
                if (partnerSorszam != betegSorszam)
                {
                    kapcsolo2++;
                }
            }

            if (populacio[partnerSorszam] == 1)
            {
                printf("partner allapot: %d \n", populacio[partnerSorszam]);
                if (vsz < 10)
                {
                    populacio[betegSorszam] = 1;
                    printf("megfertozodott: %d \n", populacio[betegSorszam]);
                }
            }
            kapcsolo++;
        }
    }

    return populacio;
}

int main()
{
    srand(time(NULL));
    remove("Q1.csv");
    int feladat = 1;
    int i, j;
    int *kezdeti_betegek;
    int *populacio_lista;

    int erzekeny = 0;
    int beteg = 1;
    int gyogyult = 2;

    int erzekeny_tomb[10000];
    int beteg_tomb[10000];
    int gyogyult_tomb[10000];

    int erzekeny_letszam = 9990;
    int beteg_letszam = 10;
    int gyogyult_letszam = 0;

    int fertoz = rand() % (100 - 1) + 1;
    int gyogyul = rand() % (100 - 1) + 1;

    printf("alfa: %d\n", fertoz);
    printf("beta: %d\n", gyogyul);

    int varos_letszam = 10000;

    // legenerálom a 10 beteg személy sorszámát, 2 azonos sorszám nem lehet
    kezdeti_betegek = RandomBetegGenerator(1, 9999, 10);


    // feltöltöm a populaciot a kezdeti állapotra (10beteggel)
    populacio_lista = BetegListaGenerator(kezdeti_betegek, 10000, erzekeny, beteg);



    int futas = 0;

    int end = 2;
    int vege = 0;
    for (j = 0; j < 50; j++)
    {

        //Lefuttatom N-szer az elemi ciklust
        for (i = 0; i < 10000; i++)
        {
            futas++;
            //  kezdeti_betegek = ElemiCiklus(kezdeti_betegek, erzekeny, beteg, gyogyult, 1, 9999);
            int kapcsolo = 0, kapcsolo2 = 0;

            while (kapcsolo == 0)
            {
                //beteg kiválasztása
                int betegSorszam = rand() % (10000 - 1) + 1;

                //ha gyógyult
                if (kezdeti_betegek[betegSorszam] == 2)
                {
                }
                //ha beteg
                if (kezdeti_betegek[betegSorszam] == 1)
                {
                    int vsz = rand() % (101 - 1) + 1;
                    if (vsz < gyogyul)
                    {
                        printf("\nBeteg - vsz: %d gyogyul: %d letszam: %d i: %d\n", vsz, gyogyul, beteg_letszam, i);

                        printf("\nGYOGYULAS elotti sorszam: %d\n", kezdeti_betegek[betegSorszam]);
                        gyogyult_letszam++;
                        beteg_letszam--;
                        if (beteg_letszam <= 0)
                        {
                            printf("\nvsz: %d gyogyul: %d letszam: %d i: %d\n", vsz, gyogyul, beteg_letszam, i);
                        }
                        kezdeti_betegek[betegSorszam] = 2;
                        printf("\nGYOGYULAS utani sorszam: %d\n", kezdeti_betegek[betegSorszam]);
                    }
                    kapcsolo++;
                }
                //ha érzékeny
                if (kezdeti_betegek[betegSorszam] == 0)
                {

                    int vsz = rand() % (101 - 1) + 1;
                    int partnerSorszam;
                    while (kapcsolo2 == 0)
                    {
                        //partner generálása, ha ugyanaz a sorszáma, random partner újra
                        partnerSorszam = rand() % (10000 - 1) + 1;
                        if (partnerSorszam != betegSorszam)
                        {
                            kapcsolo2++;
                        }
                    }
                    //ha a partner beteg
                    if (kezdeti_betegek[partnerSorszam] == 1)
                    {

                        if (vsz < fertoz)
                        {
                            beteg_letszam++;
                            erzekeny_letszam--;
                            kezdeti_betegek[betegSorszam] = 1;
                            // printf("betegletszam: %d , futas: %d\n", beteg_letszam, futas);
                        }
                    }
                    kapcsolo++;
                }
            }

            erzekeny_tomb[i] = erzekeny_letszam;
            beteg_tomb[i] = beteg_letszam;
            gyogyult_tomb[i] = gyogyult_letszam;
        }
        create_marks_csv(erzekeny_tomb, beteg_tomb, gyogyult_tomb, feladat, j);
    }

    return 0;
}

int randVsz(const int nMin, const int nMax)
{
    int r = rand() % (nMax - nMin) + nMin;
    return r;
}