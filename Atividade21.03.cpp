#include <iostream>
#include <unistd.h> // Biblioteca para usar fork() e sleep()
#include <sys/types.h> // Para definir tipos de PID
#include <sys/wait.h> // Para usar a função wait()

using namespace std;

int main() {
    // A chamada fork() cria um novo processo, que é uma cópia do processo que chamou a função
    // O processo que chamou a função é chamado de processo pai, e o novo processo é chamado de processo filho
    // O processo filho é uma cópia exata do processo pai, exceto pelo PID (Process Identifier, ou Identificador de Processo) que é um número único atribuído pelo sistema operacional a cada processo em execução no sistema
    // O processo filho recebe PID 0
    // O processo pai recebe o PID do processo filho
    // Ele serve para identificar de forma exclusiva um processo durante o tempo em que está ativo.
    pid_t pid1 = fork();
    pid_t pid2 = fork();

    // Verifica se houve erro ao criar o processo
    // Se fork() retornar -1, significa que houve um erro ao criar o processo
    if(pid1 == -1){
        cerr << "Erro ao criar processo 1!" << endl;
        return 1; // Se houve erro, retorna 1 para indicar falha
    }

    if(pid2 == -1){
        cerr << "Erro ao criar processo 2!" << endl;
        return 1; // Se houve erro, retorna 1 para indicar falha
    }

    // Bloco de código que será executado pelo processo filho
    // O código dentro do if(pid == 0) será executado pelo processo filho
    // A função sleep(5) simula uma tarefa que leva 5 segundos para ser concluída
    if(pid1 == 0){
        cout << "Inicio do processo filho!" << endl;
        sleep(5); // O processo filho simula um trabalho de 5 segundos
        cout << "Fim do processo filho!" << endl;
        return 0; // Finaliza o processo filho de forma controlada
    } else{
        // O código dendo do else será executado pelo processo pai
        // Ele chama wait(NULL), que faz o processo pai aguardar até que o processo filho termine
        cout << "Processo pai esperando o término do filho..." << endl;
        wait(NULL); // O processo pai espera o filho terminar
        cout << "Processo pai terminou!" << endl;
    }

    return 0; // Finaliza o processo pai de forma controlada
}