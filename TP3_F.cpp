#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

struct Causas{
    int id_causa;
    int fecha_ingreso;
    int id_origen;
    char origen[50];
}; 
struct Pericias{
    int id_pericia;
    int id_tipopericia;
    int fecha;
    char tipopericia[100];
};
struct RCP
{
    int id_causa;
    int id_pericia;
};

void crearArchivoBIN(FILE* f){
    char nombre[30];
    cout<<"Ingrese nombre del archivo"<<endl;
    cin.getline(nombre,30,'\n');
    f=fopen(nombre, "wb");
    fclose(f);
}

void cargarCausas(FILE* f, Causas r){
    f=fopen("CAUSAS.DAT","ab");
    cout<<"ingrese ID causa"<<endl; cin>>r.id_causa;
    cout<<"ingrese fecha de ingreso"<<endl; cin>>r.fecha_ingreso;
    cout<<"ingrese ID Origen"<<endl; cin>>r.id_origen;
    cin.ignore();
    cout<<"ingrese origen"<<endl; cin.getline(r.origen,50,'\n');
    fwrite(&r,sizeof(Causas),1,f);
    fclose(f);
}
void cargarPericias(FILE* f, Pericias r){
    f=fopen("PERICIAS_INFORMATICAS.DAT","ab");
    cout<<"ingrese ID pericia"<<endl; cin>>r.id_pericia;
    cout<<"ingrese ID tipopericia"<<endl; cin>>r.id_tipopericia;
    cout<<"ingrese fecha"<<endl; cin>>r.fecha;
    cin.ignore();
    cout<<"ingrese tipopericia"<<endl; cin.getline(r.tipopericia,100,'\n');
    fwrite(&r,sizeof(Pericias),1,f);
    fclose(f);
}
void cargarRelCyP(FILE* f, RCP r){
    f=fopen("REL_CAUSA_PERICIA.DAT","ab");
    cout<<"ingrese ID causa"<<endl; cin>>r.id_causa;
    cout<<"ingrese ID pericia"<<endl; cin>>r.id_pericia;
    fwrite(&r,sizeof(RCP),1,f);
    fclose(f);
}

void leerCausa(FILE* f){
    Causas c; int a;
    f=fopen("CAUSAS.DAT","rb");
    fread(&c,sizeof(Causas),1,f);
    cout<<"==========================="<<endl;
    while(!feof(f)){
        cout<<"ID CAUSA: "<<c.id_causa<<endl;
        cout<<"FECHA DE INGRESO: "<<c.fecha_ingreso<<endl;
        cout<<"ID ORIGEN: "<<c.id_origen<<endl;
        cout<<"ORIGEN: "<<c.origen<<endl;
        cout<<"==========================="<<endl;
        fread(&c,sizeof(Causas),1,f);
    }
    fclose(f);
    cout<<"Continuar? SI=1"<<endl;
    cin>>a;
    if(a==1) return;
}
void leerPericia(FILE* f){
    Pericias p; int a;
    f=fopen("PERICIAS_INFORMATICAS.DAT","rb");
    fread(&p,sizeof(Pericias),1,f);
    cout<<"==========================="<<endl;
    while(!feof(f)){
        cout<<"ID PERICIAS: "<<p.id_pericia<<endl;
        cout<<"ID TIPOPERICIA: "<<p.id_tipopericia<<endl;
        cout<<"Fecha: "<<p.fecha<<endl;
        cout<<"TIPOPERICIA: "<<p.tipopericia<<endl;
        cout<<"==========================="<<endl;
        fread(&p,sizeof(Pericias),1,f);
    }
    fclose(f);
    cout<<"Continuar? SI=1"<<endl;
    cin>>a;
    if(a==1) return;
}
void leerRCP(FILE* f){
    RCP cp; int a;
    f=fopen("REL_CAUSA_PERICIA.DAT","rb");
    fread(&cp,sizeof(RCP),1,f);
    cout<<"==========================="<<endl;
    while(!feof(f)){
        cout<<"ID CAUSA: "<<cp.id_causa<<endl;
        cout<<"ID PERICIAS: "<<cp.id_pericia<<endl;
        cout<<"==========================="<<endl;
        fread(&cp,sizeof(RCP),1,f);
    }
    fclose(f);
    cout<<"Continuar? SI=1"<<endl;
    cin>>a;
    if(a==1) return;
}
void leerArchivo(FILE * f){
   int c;
   cout<<"1- Leer archivo CAUSAS.DAT"<<endl;
   cout<<"2- Leer archivo PERICIAS_INFORMATICAS.DAT"<<endl;
   cout<<"3- Leer archivo REL_CAUSA_PERICIA.DAT"<<endl;
    
   cout<<"Ingrese la opcion a realizar: "<<endl;
   cin>>c;
   
   if(c==1){
    leerCausa(f);
   }
   else if(c==2){
    leerPericia(f);
   }
   else if(c==3){
    leerRCP(f);
   } 
}

void ordenamiento(Causas x[]){
    int i,j;
    Causas aux;
    for(i=0;i<11;i++){
       for(j=0;j<10;j++){
            if(x[j].fecha_ingreso>x[j+1].fecha_ingreso){
                aux.id_causa=x[j].id_causa;
                x[j].id_causa=x[j+1].id_causa;
                x[j+1].id_causa=aux.id_causa;

                aux.fecha_ingreso=x[j].fecha_ingreso;
                x[j].fecha_ingreso=x[j+1].fecha_ingreso;
                x[j+1].fecha_ingreso=aux.fecha_ingreso;
                
                aux.id_origen=x[j].id_origen;
                x[j].id_origen=x[j+1].id_origen;
                x[j+1].id_origen=aux.id_origen;
                
                strcpy(aux.origen,x[j].origen);
                strcpy(x[j].origen,x[j+1].origen);
                strcpy(x[j+1].origen,aux.origen); 
            }
       }
    }
}
void crearReporte(FILE* f){
    Causas c, S[11];
    int i=0,cantC=1,a;
    f=fopen("CAUSAS.DAT","rb");
    fread(&c,sizeof(Causas),1,f);
    while(!feof(f)){
        S[i].id_causa=c.id_causa;
        S[i].fecha_ingreso=c.fecha_ingreso;
        S[i].id_origen=c.id_origen;
        strcpy(S[i].origen,c.origen);
        i++;
        fread(&c,sizeof(Causas),1,f);
    }
    fclose(f);

    ordenamiento(S);

    for(int s=0;s<11;s++){
        for(int d=s+1; d<11;d++){
           if(!(strcmp(S[s].origen,S[d].origen)) && (S[s].fecha_ingreso/100%100==S[d].fecha_ingreso/100%100)){
                cantC++;
           }
        }
        cout<<"=================================================================================="<<endl;
        cout<<"ANIO: "<<(S[s].fecha_ingreso/10000)<<" MES: "<<(S[s].fecha_ingreso/100%100)<<"    "<<"ORIGEN: "<<S[s].origen<<endl;
        cout<<"Cantidad de causas ingresadas: "<<cantC<<endl;
        if((S[s].id_origen==S[s+1].id_origen) && (S[s].fecha_ingreso/100%100==S[s+1].fecha_ingreso/100%100)){
            s++;
        }
        cantC=1;
    } 
    cout<<"=================================================================================="<<endl;
    cout<<"Continuar? SI=1"<<endl;
    cin>>a;
    if(a==1) return;

}

void ordenamientoId(Pericias x[]){
    int i,j;
    Pericias aux;
    for(i=0;i<9;i++){
       for(j=0;j<8;j++){
            if(x[j].id_pericia>x[j+1].id_pericia){
                aux.id_pericia=x[j].id_pericia;
                x[j].id_pericia=x[j+1].id_pericia;
                x[j+1].id_pericia=aux.id_pericia;

                aux.id_tipopericia=x[j].id_tipopericia;
                x[j].id_tipopericia=x[j+1].id_tipopericia;
                x[j+1].id_tipopericia=aux.id_tipopericia;
                
                aux.fecha=x[j].fecha;
                x[j].fecha=x[j+1].fecha;
                x[j+1].fecha=aux.fecha;
                
                strcpy(aux.tipopericia,x[j].tipopericia);
                strcpy(x[j].tipopericia,x[j+1].tipopericia);
                strcpy(x[j+1].tipopericia,aux.tipopericia); 
            }
       }
    }
}
void ordenamientoId2(RCP x[]){
    int i,j;
    RCP aux;
    for(i=0;i<8;i++){
       for(j=0;j<7;j++){
            if(x[j].id_pericia>x[j+1].id_pericia){
                aux.id_causa=x[j].id_causa;
                x[j].id_causa=x[j+1].id_causa;
                x[j+1].id_causa=aux.id_causa;

                aux.id_pericia=x[j].id_pericia;
                x[j].id_pericia=x[j+1].id_pericia;
                x[j+1].id_pericia=aux.id_pericia;
                
            }
       }
    }
}
void crearReporte2(FILE* f){
    RCP CP,R[8]; Causas C, S[11]; Pericias P, PP[9];
    int i=0,cantC=0,a;
    f=fopen("CAUSAS.DAT","rb");
    fread(&C,sizeof(Causas),1,f);
    while(!feof(f)){
        S[i].id_causa=C.id_causa;
        S[i].fecha_ingreso=C.fecha_ingreso;
        S[i].id_origen=C.id_origen;
        strcpy(S[i].origen,C.origen);
        i++;
        fread(&C,sizeof(Causas),1,f);
    }
    fclose(f);
    i=0;
    f=fopen("PERICIAS_INFORMATICAS.DAT","rb");
    fread(&P,sizeof(Pericias),1,f);
    while(!feof(f)){
        PP[i].id_pericia=P.id_pericia;
        PP[i].id_tipopericia=P.id_tipopericia;
        PP[i].fecha=P.fecha;
        strcpy(PP[i].tipopericia,P.tipopericia);
        i++;
        fread(&P,sizeof(Pericias),1,f);
    }
    fclose(f);
    i=0;
    f=fopen("REL_CAUSA_PERICIA.DAT","rb");
    fread(&CP,sizeof(RCP),1,f);
    while(!feof(f)){
        R[i].id_causa=CP.id_causa;
        R[i].id_pericia=CP.id_pericia;
        i++;
        fread(&CP,sizeof(RCP),1,f);
    }
    fclose(f);

    ordenamientoId(PP);
    ordenamientoId2(R);
    ordenamiento(S);

    for(int n=0;n<9;n++){
        for(int l=0;l<8;l++){
            if(PP[n].id_pericia==R[l].id_pericia){
                for(int s=0;s<11;s++){
                    if(R[l].id_causa==S[s].id_causa){
                        cout<<"----------------------------------------------------------------------------------------------------"<<endl;
                        cout<<"TIPO PERICIA: "<<PP[n].tipopericia<<"           "<<"ORIGEN: "<<S[s].origen<<endl;
                        for(int k=0;k<11;k++){
                            if(!(strcmp(S[s].origen,S[k].origen)) && (S[s].fecha_ingreso/100%100==S[k].fecha_ingreso/100%100)){
                                cantC++;
                            }
                        }
                        cout<<"Cantidad de causas Ingresadas: "<<cantC<<endl;
                        cantC=0;
                    }
                }
            }
        }
    } 
    cout<<"==========================================================================================="<<endl;
    cout<<"Continuar? SI=1"<<endl;
    cin>>a;
    if(a==1) return;

}

int main(int argc, const char** argv) {
    int op,X=2; Causas c; Pericias p; RCP cp;
    FILE* Archivos; FILE* causasArchivo; FILE* periciasArchivo; FILE* RelCyPArchivo; FILE* ReportCausa;
    FILE* ReporteRELCyP;
    
    do{
       cout<<"1- Crear Archivos Binarios"<<endl;
       cout<<"2- Cargar Causas"<<endl;
       cout<<"3- Cargar Pericias"<<endl;
       cout<<"4- Cargar Relacion Causa y Pericia"<<endl;
       cout<<"5- Publicacion reporte Estadistico CAUSAS.DAT"<<endl;
       cout<<"6- Publicacion reporte Estadistico PERICIAS_INFORMATICAS.DAT y REL_CAUSA_PERICIA.DAT"<<endl;
       cout<<"7- Leer archivo"<<endl;
       cout<<"8- FINALIZAR"<<endl;

       cout<<"Ingrese la opcion a realizar: "<<endl;
       cin>>op;
       cin.ignore();

       switch (op)
       {
        case 1:
            system("cls");
            crearArchivoBIN(Archivos);
        break;
        case 2:
            system("cls");
            cargarCausas(causasArchivo,c);
        break;
        case 3:
            system("cls");
            cargarPericias(periciasArchivo,p);
        break;
        case 4:
            system("cls");
            cargarRelCyP(RelCyPArchivo,cp);
        break;
        case 5:
            system("cls");
            crearReporte(ReportCausa);
        break;
        case 6:
            system("cls");
            crearReporte2(ReporteRELCyP);
        break;
        
        case 7:
            system("cls");
            leerArchivo(Archivos);
        break;
    
        default:
        break;
       }
    }while (op!=8);
    
}