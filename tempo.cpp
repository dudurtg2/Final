#include <stdio.h>
#include <time.h> //necessário para usar localtime() e struct tm
int main(void)
{
  //ponteiro para struct que armazena data e hora  
  struct tm *data_hora_atual;     
  


  
  //para acessar os membros de uma struct usando o ponteiro
  //utilizamos o operador -> no nosso caso temos: 
  //data_hora_atual->membro_da_struct
  
  //Acessando dados convertidos para a struct data_hora_atual  
  printf("\nDia..........: %d\n", data_hora_atual->tm_mday);  
  
  //para retornar o mês corretamente devemos adicionar +1 
  //como vemos abaixo
  printf("\nMes..........: %d\n", data_hora_atual->tm_mon+1);
  
  //para retornar o ano corretamente devemos adicionar 1900 
  //como vemos abaixo
  printf("\nAno..........: %d\n\n", data_hora_atual->tm_year+1900);  
  
  printf("\nDia do ano...: %d\n", data_hora_atual->tm_yday);  
  printf("\nDia da semana: %d\n\n", data_hora_atual->tm_wday);
    
  /* Obtendo os valores da struct data_hora_atual  
    e formatando a saída de dados no formato 
    hora: minuto: segundo
     
  Para não ficar um printf muito longo em uma única linha
  de comando, quebrei a impressão em 3 partes mostrando
  uma informação em cada linha 
  */  
  printf("\nHora %d:",data_hora_atual->tm_hour + (((data_hora_atual->tm_mday + 2)- data_hora_atual->tm_mday)*24 ));//hora   
 
  
  /* Obtendo os valores da struct data_hora_atual  
     e formatando a saída de dados no formato dia/mes/ano 
     
     Para não ficar um printf muito longo em uma única 
     linha de comando, quebrei a impressão em 3 partes
     sendo uma informação em cada linha   
  */  
  //dia do mês
  printf("\nData ........: %d/", data_hora_atual->tm_mday);
  printf("%d/",data_hora_atual->tm_mon+1); //mês
  printf("%d\n\n",data_hora_atual->tm_year+1900); //ano
  
  return 0;
}