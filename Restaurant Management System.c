#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct items{
    char item[20];
    float price;
    int qty;
};
struct orders{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};
//functions to generate biils
void generateBillHeader(char name[50],char date[30]){
    printf("\n\n");
        printf("\t    EDIBLE ADVENTURES. Restaurant");
        printf("\n\t   -----------------");
        printf("\nDate:%s",date);
        printf("\nInvoice To: %s",name);
        printf("\n");
        printf("---------------------------------------\n");
        printf("Items\t\t");
        printf("Qty\t\t");
        printf("Total\t\t");
        printf("\n---------------------------------------");
        printf("\n\n");
}
void generateBillBody(char item[30],int qty, float price){
    printf("%s\t\t",item); 
        printf("%d\t\t",qty); 
        printf("%.2f\t\t",qty * price); 
        printf("\n");
}
void generateBillFooter(float total){
    printf("\n");
    float dis = 0.1*total;
    float netTotal=total-dis;
    float cgst=0.09*netTotal,grandTotal=netTotal + 2*cgst;//netTotal + cgst + sgst
    printf("---------------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
    printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nCGST @9%s\t\t\t%.2f","%",cgst);
    printf("\nSGST @9%s\t\t\t%.2f","%",cgst);
    printf("\n---------------------------------------");
    printf("\nGrand Total\t\t\t%.2f",grandTotal);
    printf("\n---------------------------------------\n");
}
void displayFoodMenu() {
    printf("\n\t\t=== FOOD MENU ===");
    printf("\n1. Dish 1 - $10.99");
    printf("\n2. Dish 2 - $8.49");
    printf("\n3. Dish 3 - $12.99");
    printf("\n4. Dish 4 - $15.23");
    printf("\n5. Dish 5 - $10.99");
    printf("\n6. Dish 6 - $8.49");
    printf("\n7. Dish 7 - $12.99");
    printf("\n8. Dish 8 - $15.23");
    printf("\n9. Dish 9 - $10.99");
    printf("\n10. Dish 10 - $8.49");
    printf("\n11. Dish 11 - $12.99");
    printf("\n12. Dish 12 - $15.23");
    printf("\n13. Dish 13 - $8.49");
    printf("\n14. Dish 14 - $12.99");
    printf("\n15. Dish 15 - $15.23");
    printf("\n16. Dish 16 - $10.99");
    printf("\n17. Dish 17 - $8.49");
    printf("\n18. Dish 18 - $12.99");
    printf("\n19. Dish 19 - $15.23");
    printf("\n20. Dish 20 - $8.49");
    printf("\n21. Dish 21 - $12.99");
    printf("\n22. Dish 22 - $15.23");
    printf("\n23. Dish 23 - $10.99");
    printf("\n24. Dish 24 - $8.49");
    printf("\n25. Dish 25 - $12.99");
    // Add more items as needed
    printf("\n\n");
}
int main(){
    int opt,n;
    struct orders ord;
    struct orders order;
    char saveBill = 'y',contFlag = 'y';
    char name[50];
    FILE *fp;
       //dashboard
    while(contFlag == 'y'){
    system("clear");
    float total = 0;
    int invoiceFound = 0;
    printf("\t============The Edibles . RESTAURANT============");
    printf("\n\nPlease select your prefered operation");
    printf("\n\n1.Generate Invoice");
    printf("\n2.Show all Invoices");
    printf("\n3.Search Invoice");
    printf("\n4.Display food menu");
    printf("\n5.Exit");
    printf("\n\nYour choice:\t");
    scanf("%d",&opt);
    fgetc(stdin);
    switch(opt){
        case 1:
        system("clear");
        printf("\nPlease enter the name of the customer:\t");
        fgets(ord.customer,50,stdin);
        ord.customer[strlen(ord.customer)-1] = 0;
        printf("\nPlease enter the number of items:\t");
        scanf("%d",&n);
        ord.numOfItems = n;
        for(int i=0;i<n;i++){
            fgetc(stdin);
            printf("\n\n");
            printf("Please enter the item %d:\t",i+1);
            fgets(ord.itm[i].item,20,stdin);
            ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
            printf("Please enter the quantity:\t");
            scanf("%d",&ord.itm[i].qty);
            printf("Please enter the unit price:\t");
            scanf("%f",&ord.itm[i].price);
            total += ord.itm[i].qty * ord.itm[i].price;
        }
        generateBillHeader(ord.customer,ord.date);
        for(int i=0;i<ord.numOfItems;i++){
            generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
        }
        generateBillFooter(total);
        printf("\nDo you want to save the invoice [y/n]:\t");
        scanf("%s",&saveBill);
        if(saveBill == 'y'){
            fp = fopen("RestaurantBill.dat","a+");
            fwrite(&ord,sizeof(struct orders),1,fp);
            if(fwrite != 0)
            printf("\nSuccessfully saved");
            else 
            printf("\nError saving");
            fclose(fp);
        }
        break;
        case 2:
        system("clear");
        fp = fopen("RestaurantBill.dat","r");
        printf("\n  ****Your Previous Invoices****\n");
        while(fread(&order,sizeof(struct orders),1,fp)){
            float tot = 0;
            generateBillHeader(order.customer,order.date);
            for(int i=0;i<order.numOfItems;i++){
                generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                tot+=order.itm[i].qty * order.itm[i].price;
            }
            generateBillFooter(tot);
        }
        fclose(fp);
        break;
        case 3:
        printf("Enter the name of the customer:\t");
        //fgetc(stdin);
        fgets(name,50,stdin);
        name[strlen(name)-1] = 0;
        system("clear");
        fp = fopen("RestaurantBill.dat","r");
        printf("\t****Invoice of %s****",name);
        while(fread(&order,sizeof(struct orders),1,fp)){
            float tot = 0;
            if(!strcmp(order.customer,name)){
            generateBillHeader(order.customer,order.date);
            for(int i=0;i<order.numOfItems;i++){
                generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                tot+=order.itm[i].qty * order.itm[i].price;
            }
            generateBillFooter(tot);
            invoiceFound = 1;
            }
        }
        if(!invoiceFound){
            printf("Sorry the invoice for %s doesnot exists",name);
        }
        fclose(fp);
        break;
    case 4:
     printf("Display the food menu");
     displayFoodMenu();
     break;
    case 5:
    printf("\n\t\t Bye Bye :)\n\n");
    exit(0);
    break;
    default:
    printf("Sorry invalid option");
    break;
    }
    printf("\nDo you want to perform another operation?[y/n]:\t");
    scanf("%s",&contFlag);
    }
    printf("\n\t\t Bye Bye :)\n\n");
    printf("\n\n");
    return 0;
}