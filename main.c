
#include <stdio.h>
#include <stdlib.h>


char str[1000];
double num[1000] = {0};
int usend[1000] = {0};//優先度 処理順を決める
int cram(int a);
int mozisu,mode =0;


int main(void) {
    printf("半角でお願いします 使える文字は 0123456789 +-*/ ()のみです\n式の文字数は100文字以下でお願いします\n負の数には()をつけてください\n4*-5等と書くと正しい結果が出力されません 4*(-5)としてください\nqを入力すると終了します");
    while(1){
        printf("\n式を入れてください\n");
        if(mode == 2){
            printf("%f",num[0]);
        }
        fgets(str,999,stdin);
        if(str[0] =='q'){
            break;
        }
        puts(str);
        
        if(str[0]== '\n'){//modechange
            printf("引き継ぎモードに切り替えます");
            printf("\n式を入れてください\n");
            fgets(str,999,stdin);
            puts(str);
            mode = 1;
        }

        int a=0,m=0;
        double tasu =43, kakeru = 42.0, hiku =45,waru =47.0,open =40.0,close = 41.0;
    
        if(mode<2){//引き継ぎモードの時の処理
            for(int h = 0; h<990; h++){
                num[h]=str[h];//  ASCII codeに変換
            }
        }
        if(mode==2){
            for(int h = 0; h<990; h++){
                num[h+1]=str[h];//  ASCII codeに変換
            }
        }
        for(int i = 0; i <900; i ++){//文字の読み込み
            if(mode==2&&i==0){//引き継ぎモードの時の処理
                i++;
            }
            if((num[i]-48) >= 0&& (num[i]-48) < 9){ //0-9の時の処理
                num[i]-=48;
            }else if( num[i]==40 ||num[i]==41 ||num[i]==42 ||num[i]==43 ||num[i]==45 ||num[i]==47 ){//()*+-/ の処理
                usend[i]=1;
            }
            else if(num[i]==10){//改行記号の処理
                mozisu = i;
                usend[i]= -1;
                num[i] =100;
                break;
            }
            else if(num[i]!= 0){ //関係ない文字の削除
                cram(i);
                i--;
            }
        }
    
    
        for(int j = 0; j < mozisu; j ++){// 2桁以上の整数を一箇所にまとめて、ずらす
            if( usend[j]==0 &&usend[j+1]==0 ){
                num[j] = num[j]*10 + num[ j + 1];
                cram(j+1);
                j--;
            }
        }
    
    
        for(int k =0; k < mozisu; k++){ // ()の処理
            if(num[k] == open){//優先度の割り振り
                a++;
                for(int l =k+1; l<100;l++){
                    if(num[l] == open){
                        a++;
                    }
                    if(num[l]== close){
                        a --;
                        if(a == 0){
                            for(m = k; m < l; m++){
                                if(usend[m]>0){
                                    usend[m]++;
                                }
                            }
                            cram(m);
                            cram(k);
                            l=100;//ループ脱出
                            k--;
                        }
                    }
                }
            }
        }
        for(int use = 500; use>0; use--){//四則演算プログラム
            for(int ii=0; ii  <mozisu; ii++){
                if(usend[ii] == use){
                    if( num[ii] == hiku ){
                        if( ii == 0 ){
                            num[ii+1] = (-1)*num[ii+1];
                            cram(ii);
                            ii = mozisu;
                        }else if(usend[ii-1]>0){
                            num[ii+1]=(-1)*num[ii+1];
                            cram(ii);
                            ii = 0;
                        }
                    }
                    if(num[ii] == kakeru){//掛け算
                        num[ii-1] = num[ii-1] * num[ii+1];
                        cram(ii+1);
                        cram(ii);
                        ii = 0;
                    }
                    if(num[ii] == waru){//割り算
                        num[ii-1] = num[ii-1] * num[ii+1];
                        cram(ii+1);
                        cram(ii);
                        ii = 0;
                    }
                }
            }
            for(int jj = 0; jj < mozisu; jj++){
                if(usend[jj]==use){
                    if(num[jj] == hiku){//引き算
                        num[jj-1] = num[jj-1] - num[jj+1];
                        cram(jj+1);
                        cram(jj);
                    }
                    if(num[jj] == tasu){//足し算
                        num[jj-1] = num[jj-1] + num[jj+1];
                        cram(jj+1);
                        cram(jj);
                        jj = 0;
                    }
                }
            }
        }
        if(mozisu!=1){
            printf("計算に失敗しました");
            printf("%d\n",mozisu);
        }
        for(int n = 0; n<mozisu; n++){
            printf("%f",num[n]);
        }
        for(int v = 0; v<999 ;v++){
            usend[v]=0;
            num[v+1]=0;
        }
        if(mode ==1) {
            mode = 2;
        }
    }
    return 0;
}


int cram( int a ){ //与えられた番号のnumとusendを消して左に詰める
    for(int zm = a; zm < 100; zm++){
        num[zm] = num[zm+1];
        usend[zm] = usend[zm+1];
    }
    mozisu--;
    return 0;
}
