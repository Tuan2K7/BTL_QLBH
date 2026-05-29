#include "hoa_don.h"
#include "menu.h"


// TAO HOA DON MOI                                                    

int tao_hoa_don(void) { // void ko nhan tham so nao ca 
    int ma_mon, cap_do, i, tim_thay;
    HoaDon *hd; // hd la con tro kieu HoaDon

    if (so_hoa_don >= MAX_HOA_DON) {
        printf("Da dat toi da so luong hoa don!\n");
        return -1;
    }

    hd = &ds_hoa_don[so_hoa_don]; // lay dia chi ,mmoji thứ viết qua hd-> đều tác độg trực tiếp vào ô đó trong mảng
    hd->so_hd   = so_hoa_don + 1;// ds_hoa_don[i].so_hd = ..
    hd->so_item = 0; //same
    hd->tong_tien = 0; //ds_hoa_don[i].tong_tien +=

    hien_thi_menu(); // hiển thị menu trong phần menu.c
    printf("\n--- DAT MON CHO HOA DON #%d ---\n", hd->so_hd);

    while (1) { // while(true)  phần này là phần sẽ nhập món theo số
        /* --- Nhap mon --- */
        printf("\nNhap so thu tu mon (1-6), nhap 0 de ket thuc: ");
        if (scanf("%d", &ma_mon) != 1) { 
            while(getchar()!='\n'); 
            continue; 
                    }

        if (ma_mon == 0) break;
        if (ma_mon < 1 || ma_mon > MAX_MON) {
            printf("So thu tu khong hop le! Vui long nhap lai.\n");
            continue;
        }

        /* --- Nhap cap do --- */
        printf("Nhap cap do cay (1-7): ");
        if (scanf("%d", &cap_do) != 1) {  // nếu mà nhập chữ thì sẽ ko có gì sảy ra cả,nó sẽ lặp lại và đợi ta nhập số
             while(getchar()!='\n'); 
             continue; 
                    }
        if (cap_do < 1 || cap_do > MAX_CAP_DO) { //ktra
            printf("Cap do khong hop le! Vui long nhap lai.\n");
            continue;
        }

        /* --- Tim xem da co cung mon + cap do chua --- */
        tim_thay = 0;
        for (i = 0; i < hd->so_item ; i++) { 
            //vong 1 hdsoitem =0 ; vong 2; hdsoitem = 1; for (i=0 ;i < 1;i++)
            // vong 1 i =0 mi kim chi cap 1
            // vong 2 i = 1 mi thai cap 2
            // vong 3 i =2 mi kim cap 1 ma_mon = mi kim chi va cap_do = 1
            if (hd->items[i].ma_mon == ma_mon && hd->items[i].cap_do == cap_do) {
                hd->items[i].so_luong++;
                hd->items[i].thanh_tien = hd->items[i].so_luong * hd->items[i].don_gia;
        
                printf("  >> Tang so luong: %s Cap %d x%d\n",
                       menu[ma_mon-1].ten, cap_do, hd->items[i].so_luong);
                tim_thay = 1;
                break;
            }
        }

        /* --- Neu chua co, them item moi --- */
        if (!tim_thay) { // !0 = true , else false
            if (hd->so_item >= MAX_ITEM) {
                printf("Hoa don da day! Khong the them mon.\n");
                continue;
            }
            hd->items[hd->so_item].ma_mon    = ma_mon;
            hd->items[hd->so_item].cap_do    = cap_do;
            hd->items[hd->so_item].so_luong  = 1;
            hd->items[hd->so_item].don_gia   = menu[ma_mon-1].don_gia;
            hd->items[hd->so_item].thanh_tien= menu[ma_mon-1].don_gia;
            printf("  >> Da them: %s Cap %d\n",
                   menu[ma_mon-1].ten, cap_do);
            hd->so_item++;
        }
    }

    if (hd->so_item == 0) {
        printf("Khong co mon nao duoc dat. Huy hoa don.\n");
        return -1;
    }

    /* Tinh tong */
    hd->tong_tien = 0;
    for (i = 0; i < hd->so_item; i++)
        hd->tong_tien += hd->items[i].thanh_tien;

    so_hoa_don++;
    printf("\n>> Da luu Hoa Don #%d thanh cong!\n", hd->so_hd);
    //return hd->so_hd; 
    return 1;
}


//  IN NOI DUNG HOA DON (dung chung cho stdout & file)               

void in_noi_dung_hoa_don(FILE *fp, HoaDon *hd) {
    int i, stt;

    fprintf(fp, "============================================================\n");
    fprintf(fp, "        QUAN MI CAY UPTOmyCAY\n"); 
    fprintf(fp, "        HOA DON #%d\n", hd->so_hd);
    fprintf(fp, "============================================================\n");
    fprintf(fp, "  %-3s  %-28s  %-4s  %-7s  %s\n","STT", "Ten san pham", "SL", "Don Gia", "Thanh Tien");
    fprintf(fp, "------------------------------------------------------------\n");

    stt = 1;
    for (i = 0; i < hd->so_item; i++) {
        char ten_day_du[80];
        /* Gop ten mon + cap do */ 
        sprintf(ten_day_du, "%s Cap %d",
                menu[hd->items[i].ma_mon - 1].ten,
                hd->items[i].cap_do);

        fprintf(fp, "  %-3d  %-28s  %-4d  %7.0f  %9.0f\n",
            stt,ten_day_du,hd->items[i].so_luong,hd->items[i].don_gia,hd->items[i].thanh_tien);
            stt++;
                    }

    fprintf(fp, "------------------------------------------------------------\n");
    fprintf(fp, "  %-37s  %9.0f VND\n", "Tong so tien:", hd->tong_tien);
    fprintf(fp, "============================================================\n");
    fprintf(fp, "       Cam on quy khach! Hen gap lai.\n");
    fprintf(fp, "============================================================\n");
}


//  IN TAT CA HOA DON RA MAN HINH                                     

void in_tat_ca_hoa_don(void) {
    int i;
    if (so_hoa_don == 0) {
        printf("\nChua co hoa don nao!\n");
        return;
    }
    for (i = 0; i < so_hoa_don; i++) {
        printf("\n");
        in_noi_dung_hoa_don(stdout, &ds_hoa_don[i]);
    }
}



// XUAT HOA DON RA FILE .TXT                                         

void xuat_hoa_don_ra_file(int so_hd) {
    int  i;
    char ten_file[40];
    FILE *fp;
    HoaDon *hd = NULL; // tim xem co hoa don thu may k

    for (i = 0; i < so_hoa_don; i++) {
        if (ds_hoa_don[i].so_hd == so_hd) {
            hd = &ds_hoa_don[i]; // lúc này đã có địa chỉ thay vì là Null
            break;
        }
    }

    if (hd == NULL) {
        printf("Khong tim thay hoa don #%d!\n", so_hd);
        return;
    }

    sprintf(ten_file, "hoadon_%d.txt", so_hd);
    fp = fopen(ten_file, "w");
    if (fp == NULL) {
        printf("Khong the mo file %s!\n", ten_file);
        return;
    }

    in_noi_dung_hoa_don(fp, hd);
    fclose(fp);
    printf(">> Da xuat hoa don #%d ra file: %s\n", so_hd, ten_file);
}
