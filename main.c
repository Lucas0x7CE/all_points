#include <stdio.h>
#define l 19.4 //comprimento do patch
#define w 26  //largura do patch
#define inx 5 //total de pinos no eixo x
#define iny 5 //total de pinos no eixo y
#define diametro 2 //mm
#define modelo 0 //Com MARGEM: 1; sem MARGEM: 0
#define CSV 0

//gerador de posicoes
//o programa tem como finalidade ser uma ferramenta para projetos no ANSYS que tratam de antenas de microfita do tipo patch, essa ferramenta calcula uma serie de pontos que representam os pinos de curto circuito, os pontos sao distribuidos sobre a superficie do patch e tem espaçamento igual entre si, podendo haver margem ou nao, a presença de margem significa que o pino nao encostara no limite do patch, entao existira uma distancia entre o pino e o limite do patch

// COM MARGEM
// |_( )_( )_( )_|
// |_( )_( )_( )_|
// |_( )_( )_( )_|

// SEM MARGEM
// |( )__( )__( )|
// |( )__( )__( )|
// |( )__( )__( )|

//a utilidade desse programa consiste em prever os pontos que o programa de analise(optmetrics) percorrera, definindo o x ou y inicial e final, e o step(deslocamento x ou y)

//+Proposta: adicionar uma saida de arquivo CSV com todos os pontos

void sem_margem(float altura, float largura,float raio_c,float px, float py,int num_cinx, int num_ciny,float deslocamentox, float deslocamentoy, int contador_pino){
  altura = altura/2;
  largura = largura/2;
  py = -largura + raio_c;
  px = -altura + raio_c;
  for(int x = 0; x < num_cinx; x++){
    for(int y = 0; y < num_ciny; y++){
      if(CSV){
        printf("%.3f;%.3f\n",px,py);
      }else{
        printf("pin%d: x= %.1f | y= %.1f\n",contador_pino,px,py);
      }
      py += deslocamentoy;
      contador_pino+=1;
    }
      px += deslocamentox;
      py = -largura + 1;
  }
}
void com_margem(float altura, float largura,float raio_c,float px, float py,int num_cinx, int num_ciny,float deslocamentox, float deslocamentoy,float espacamentox, float espacamentoy, int contador_pino){
  altura = altura/2;
  largura = largura/2;
  py = -largura + espacamentoy + raio_c;
  px = -altura + espacamentox + raio_c;
  for(int x = 0; x < num_cinx; x++){
    for(int y = 0; y < num_ciny; y++){
      if(CSV){
        printf("%.3f;%.3f\n",px,py);
      }else{
        printf("pin%d: x= %.1f | y= %.1f\n",contador_pino,px,py);
      }
      py += deslocamentoy;
      contador_pino+=1;
    }
      px += deslocamentox;
      py = -largura + espacamentoy + raio_c;
  }
}
int main(void) {
  //listagem da grade de posicoes dos pinos de curto para patch
  float altura, largura;//dimensao do patch//W,L
  float diametro_c;//diametro do cilindro
  float raio_c;
  int num_cinx;//numero de cilindros na fila paralela a x
  int num_ciny;//numero de cilindros na fila paralala a y
  int total_c;//se preferir definir o total de cilindros na area do plano do patch
  float espacamentox;
  float espacamentoy;
  int nespaco_entre_cx;
  int nespaco_entre_cy;
  float deslocamentox; //diametro + espacamento
  float deslocamentoy; //diametro + espacamento
  int contador_pino=1;
  float px, py;
  int chave=1;
  int margem;
  int *parametros;

  //com(1) ou sem(0) margem
  margem = modelo;//altera o tipo de listagem
  altura = l;//mm x
  largura = w;//mm y
  diametro_c = diametro;//mm
  raio_c = diametro_c/2;
  num_cinx = inx;
  num_ciny = iny;
  
  //sem margem: num_cinxy - 1;
  //com margem: num_cinxy + 2;
  if(margem){
    nespaco_entre_cx = num_cinx + 1;
    nespaco_entre_cy = num_ciny + 1;
  }else{
    nespaco_entre_cx = num_cinx - 1;
    nespaco_entre_cy = num_ciny - 1;
  }
  espacamentox = (altura - (diametro_c*num_cinx))/nespaco_entre_cx;
  espacamentoy = (largura - (diametro_c*num_ciny))/nespaco_entre_cy;
  deslocamentox = diametro_c + espacamentox;
  deslocamentoy = diametro_c + espacamentoy;
  printf("\nALTURA: %.2fmm ; LARGURA: %.2fmm\n",altura,largura);
  printf("DIAMETRO: %2.fmm ; RAIO: %2.fmm\n",diametro_c,raio_c);
  printf("Numero de espaços entre os cilindros na fila X: %d\n",nespaco_entre_cx);
  printf("Numero de espaços entre os cilindros na fila Y: %d\n",nespaco_entre_cy);
  printf("Espaçamento entre cilindros no eixo X: %.2fmm\nEspaçamento entre cilindros no eixo Y: %.2fmm\n",espacamentox,espacamentoy);
  printf("DESLOCAMENTO(step) X: %.3f mm\nDESLOCAMENTO(step) Y: %.3f mm\n\n",deslocamentox,deslocamentoy);
  printf("TOTAL DE PONTOS: %d\n\n",inx*iny);

  if(margem){
    com_margem( altura, largura, raio_c, px, py, num_cinx, num_ciny, deslocamentox, deslocamentoy, espacamentox, espacamentoy, contador_pino);
  }else{
    sem_margem(altura,largura,raio_c,px,py,num_cinx,num_ciny,deslocamentox,deslocamentoy,contador_pino);
  }
  return 0;
}