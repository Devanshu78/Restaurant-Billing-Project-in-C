#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void header(char name[50], char date[30]);
void Bill_Body(char item[50], int qty, float price);
void footer(float total);

struct item
{
    char item[50];
    float price;
    int qty;
};
struct order
{
    char customer[50], date[50];
    int numOfitems;
    struct item itm[50];
};

int main()
{
    char savebill = 'y', name[50], contFlag = 'y';
    FILE *fp;
    int opt, n;
    struct order ord;
    struct order orders;
    while (contFlag == 'y')
    {
        float total = 0;
        int UserInvoice = 0;
        printf("\n\n\t================ Welcome to Ram Bhandar ================\n\n");
        printf("\t1. Generate Invoice\n");
        printf("\t2. Show all Invoice\n");
        printf("\t3. Search Invoice\n");
        printf("\t4. Exit\n");
        printf("\tYour Choice : ");
        scanf("%d", &opt);
        printf("-----------------------------------------------------------\n");
        fgetc(stdin);
        switch (opt)
        {
        case 1:
            printf("Enter the name : ");
            fgets(ord.customer, 50, stdin);
            ord.customer[strlen(ord.customer) - 1] = 0;
            strcpy(ord.date, __DATE__);
            printf("Number of item : ");
            scanf("%d", &n);
            ord.numOfitems = n;
            for (int i = 0; i < n; i++)
            {
                fflush(stdin);
                printf("\n");
                printf("Please enterd your itme %d\t", i + 1);
                fgets(ord.itm[i].item, 20, stdin);
                ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;
                printf("enter the quantity :\t");
                scanf("%d", &ord.itm[i].qty);
                printf("enter the unit price :\t");
                scanf("%f", &ord.itm[i].price);
                printf("\n");
                total += (ord.itm[i].qty * ord.itm[i].price);
            }
            header(ord.customer, ord.date);
            for (int i = 0; i < ord.numOfitems; i++)
            {
                Bill_Body(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
            }
            footer(total);

            printf("Do you want to save the bill [y/n] : ");
            scanf("%s", &savebill);
            if (savebill == 'y')
            {
                fp = fopen("Invoice.dat", "a+");
                fwrite(&ord, sizeof(struct order), 1, fp);
                if (fwrite != 0)
                {
                    printf("Your Invoice saved succesfully :):):)");
                }
                else
                {
                    printf("Error!!!!!");
                }
                fclose(fp);
                break;
            }

        case 2:
            fp = fopen("Invoice.dat", "r");
            printf("\n **** Your Previous Invoices ****\n");
            while (fread(&orders, sizeof(struct order), 1, fp))
            {
                float tot = 0;
                header(orders.customer, orders.date);
                for (int i = 0; i < orders.numOfitems; i++)
                {
                    Bill_Body(orders.itm[i].item, orders.itm[i].qty, orders.itm[i].price);
                    tot += (orders.itm[i].qty * orders.itm[i].price);
                }
                footer(tot);
            }
            fclose(fp);
            break;

        case 3:
            printf("Enter the Nmae of Customer : \t");
            fgets(name, 50, stdin);
            name[strlen(name) - 1] = 0;
            fp = fopen("Invoice.dat", "r");
            printf("\n **** Invoices of %s ****\n", name);
            while (fread(&orders, sizeof(struct order), 1, fp))
            {
                float tot = 0;
                if (!strcmp(orders.customer, name))
                {
                    header(orders.customer, orders.date);
                    for (int i = 0; i < orders.numOfitems; i++)
                    {
                        Bill_Body(orders.itm[i].item, orders.itm[i].qty, orders.itm[i].price);
                        tot += (orders.itm[i].qty * orders.itm[i].price);
                    }
                    footer(tot);
                    UserInvoice = 1;
                }
                if (!UserInvoice)
                {
                    printf("The %s user didn't found\n\n", name);
                }
            }
            fclose(fp);
            break;

        case 4:
            printf("\t<===== BYE  BYE BYE :):):) =====>\n\n");
            exit(0);
            break;

        default:
            printf("sorry invalid option !!!\n\n");
            break;
        }
        printf("\nDo you want to perform another task [y/n] : ");
        scanf("%s", &contFlag);
        printf("\n\n");
    }
    printf("\t<===== BYE  BYE BYE :):):) =====>\n");
    return 0;
}

void header(char name[50], char date[30])
{
    printf("\n\n");
    printf("\t\tRam Bhandar\n");
    printf("-------------------------------------------------------------\n");
    printf("Date : %s\n", date);
    printf("Invoice to : %s\n", name);
    printf("-------------------------------------------------------------\n");
    printf("Item \t\t");
    printf("Qty \t\t");
    printf("Total \t\t");
    printf("\n-------------------------------------------------------------\n\n");
}
void Bill_Body(char item[50], int qty, float price)
{
    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", qty * price);
    printf("\n");
}
void footer(float total)
{
    float dis = (0.1 * total);
    float netTotal = (total - dis);
    float cgst = (0.09 * netTotal), grandTotal = (netTotal + (2 * cgst));
    printf("-------------------------------------------------------------\n");
    printf("SubTotal \t\t\t %.2f\n", total);
    printf("Discount @10%s \t\t\t %.2f\n", "%", dis);
    printf("\t\t\t-----------------------------\n");
    printf("Net Total \t\t\t %.2f\n", netTotal);
    printf("CGST @9%s \t\t\t %.2f\n", "%", cgst);
    printf("SGST @9%s \t\t\t %.2f\n", "%", cgst);
    printf("-------------------------------------------------------------\n");
    printf("Grand Total \t\t\t %.2f", grandTotal);
    printf("\n-----------------------------------------------------------\n");
}