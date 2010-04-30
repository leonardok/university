O script recebe nomes de arquivos como argumentos (-e) contendo nomes de 
executáveis, pega o conteudo desse arquivo e tenta executar em background. O
nome dos arquivos deve ser precedido por "-e" como no exemplo:
        script -e arq.txt -e arq.txt
        
O script fica em um laço eterno lendo os argumentos que foram passados. As 
condições de parada são: 
+ ter menos de dois argumentos, exit status 0
+ ter 2 argumentos mas a opção "-e" estar errada, vai executar o comportamento
  defult, imprimir o USAGE, e sair com status -1. O seguinte exemplo demonstra o 
  comportamento:
        $ script -f arq.txt
        $ script [-e|-c] filename...

Caso sejam passados 3 argumentos para o script ele irá tentar executar os dois
primeiros argumentos e em seguida tem comportamento correspondente ao ponto 1.
Esse comportamento vai se repetir para qualquer 2n+1 numero de argumentos.

Quando o token "-e" for econtrado o conteúdo do arquivo passado a seguir é lido
e expandido dentro de outro laço, onde cada iteração corresponde a um nome de 
programa dentro deste arquivo. Para cada nome de programa passado é feito um
teste confirmando que o arquivo existe e é um executável. Se o resultado do 
teste for negativo vai pular para a próxima iteração. Se for verdade então vai
executar o programa passado redirecionando o stdout e o stderr para /dev/null.
Depois da execução do programa vai imprimir na tela o número da iteração, o nome 
do programa e o seu status de retorno. Depois disso volta para o início do loop.







