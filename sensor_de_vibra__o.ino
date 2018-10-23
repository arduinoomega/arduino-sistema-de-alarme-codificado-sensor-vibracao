#include <Keypad.h> // inclui a biblioteca do teclado matricial 4x4
#include <LiquidCrystal.h> // inclui a biblioteca para o display Lcd 16x2
#define buzzer 9 // define o pino 9 para o buzzer
#define sinal_sensor A2 // define o pino A2 para a entrada de sinal
#define led_alarme A4 // define o pino A4 para o led rgb de alarme
#define button_desativador A1 // define o pino A1 como desativador alternativo
int ativa_alarme; // Cria uma variavel int de nome ativa_alarme
int desliga_alarme; // cria uma variavel int de nome desliga_alarme
int leitura_sensor; // cria uma variavel int de nome leitura_sensor
byte pinosLinhas[] = {8,A3,10,11}; // cria um vetor de 4 colunas
byte pinosColunas[] = {A0,A5,12,13}; // cria um vetor de 4 colunas
char senha[4] = {'5','9','3','8'}; // cria um vetor char de nome senha de 4 colunas com caracteres definidos 
char vetor[4]; // cria um vetor char para armazenar os digitos do teclado
int i; // cria uma variavel de nome i
char teclas[4][4] = {{'1','2','3','A'}, // matriz 4x4 com caracteres definidos
                     {'4','5','6','B'},
                     {'7','8','9','C'},
                     {'*','0','#','D'}};

Keypad teclado1 = Keypad( makeKeymap(teclas), pinosLinhas, pinosColunas, 4, 4); // cria a variavel de nome teclado1 para armazenar os caracteres
LiquidCrystal lcd ( 7, 6, 5, 4, 3, 2); // define os pinos para comunicação com o display lcd

void setup() {
pinMode(buzzer, OUTPUT); // define o pino buzzer como saída
pinMode(sinal_sensor,INPUT); // define o pino de sinal do sensor de vibrações como entrada
pinMode(led_alarme, OUTPUT); // define o pino do led como saída
pinMode(button_desativador,INPUT); //define o desativador alternativo como entrada
lcd.begin(16,2); // inicia a comunicação com o display lcd
lcd.setCursor(0,0); lcd.print("ALARME");} // escreve ALARME no display na posição (0,0)

void loop() {
lcd.setCursor(8,0); lcd.print("OFF"); // indica que o alarme está desabiitado no display
digitalWrite (led_alarme ,LOW); // deixa o led de alarme desligado
char tecla_pressionada = teclado1.getKey(); //  verifica se alguma tecla foi pressionada 
       if (tecla_pressionada == '#' ) { // se # for pressionado executa o codigo abaixo
lcd.setCursor(8,0); lcd.print("ON "); // indica no display que o alarme está ativo
digitalWrite (buzzer, HIGH); delay(50);  // sonorização
       while ( tecla_pressionada != '*') { // enquanto * não for pressionado o programa executa no laço abaixo
leitura_sensor = digitalRead(sinal_sensor); // realiza a leitura de sinal advindo do sensor de vibrações
tecla_pressionada = teclado1.getKey(); // verifica se alguma tecla foi pressionada

//******************************************ALARME
       if (leitura_sensor == HIGH) { // se receber sinais do sensor de vibração, executa o codigo abaixo
analogWrite (buzzer, 130); delay(100); // sonorizaão alarme inicial
analogWrite (buzzer, 150); delay(200); // sonorização alarme inicial
analogWrite (buzzer, 255); delay(100); // sonorização alarme inicial 
analogWrite (buzzer, 100); delay(300); // sonorização alarme inicial
       while ( desliga_alarme != HIGH){ // enquanto o botão de desativador alternativo não for ativo, executa o laço abaixo
desliga_alarme = digitalRead(button_desativador); // realiza a leitura do botao alternativo
digitalWrite (led_alarme ,HIGH); // liga o led rgb de alarme
digitalWrite (buzzer, HIGH); delay(100); // Alarme 
digitalWrite (buzzer, LOW); delay(100); // Alarme
tecla_pressionada = teclado1.getKey(); // verifica se alguma tecla foi pressionada
//******************************************SENHA
       if (tecla_pressionada){ // se alguma tecla for pressionada executa abaixo
vetor[i] = tecla_pressionada; // armazena no vetor[4] as teclas pressionadas
lcd.setCursor(i,1); lcd.print(tecla_pressionada); // indica no display a tecla pressionada
i++; // contador para definir que a senha seja de 4 digitos
       if(i==4){ // se o ultimo digito da senha for pressionado, executa abaixo
       if(vetor[0] == senha[0] && 
          vetor[1] == senha[1] &&
          vetor[2] == senha[2] &&
          vetor[3] == senha[3]){ // compara o vetor das teclas pressionadas com a senha pré definida
lcd.setCursor(7,1); lcd.print("OK"); delay(1000); // indica que a senha digitada foi correta
lcd.setCursor(0,1); lcd.print("                "); // limpa o display
lcd.setCursor(6,0); lcd.print("                "); // limpa o display
i=0; // zera o contador
return 0;} // desativa o alarme retornando o codigo para o inicio
        else { // se a senha não for correta, executa abaixo
lcd.setCursor(0,1); lcd.print("SENHA INVALIDA  "); digitalWrite (buzzer, HIGH); delay(1000); // indica no display que a senha digitada não é correta
lcd.setCursor(0,1); lcd.print("                "); //limpa o display
i=0;} //zera o contador
}}}}    
//******************************************FIM DO ALARME
else { analogWrite(buzzer,0); // caso o alarme não estiver ativo, garante o buzzer desativado
}}}}
