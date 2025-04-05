#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

using namespace std;

void* thread_exec(void* arg){
    int id = *(int*)arg; // Converte o argumento para um inteiro (ID da thread)
    
    cout << "Thread " << id << " - Iniciando!" << endl;
    sleep(1 + id);
    cout << "Thread " << id << " - Finalizado!" << endl;

    return nullptr; // Finaliza a thread
}

int main(){
    pid_t pid1 = fork();

    if(pid1 == -1){
        cerr << "Erro ao criar o primeiro processo!" << endl;
        return 1;
    }

    // O tempo de espera dos processos, sleep, foi removido
    if(pid1 == 0){
        cout << "Inicio do processo filho 1!" << endl;

        pthread_t thread1, thread2; // Declara duas threads para o processo filho 1
        int id1 = 5, id2 = 6; // Identificador da thread do primeiro filho

        // Cria a thread dentro do processo filho 1
        pthread_create(&thread1, nullptr, thread_exec, &id1);

        pthread_create(&thread2, nullptr, thread_exec, &id2);

        // Aguarda a finalização da thread antes do processo encerrar
        pthread_join(thread1, nullptr);

        pthread_join(thread2, nullptr);

        cout << "Fim do processo filho 1!" << endl;
        return 0;
    } else {
        pid_t pid2 = fork();

        if(pid2 == -1){
            cerr << "Erro ao criar o segundo processo!" << endl;
            return 1;
        }

        if(pid2 == 0){
            cout << "Inicio do processo filho 2!" << endl;

            pthread_t thread3, thread4; // Declara duas threads para o processo filho 2
            int id3 = 1, id4 = 2; // Identificador da thread do segundo filho

            // Cria a thread dentro do processo filho 2
            pthread_create(&thread3, nullptr, thread_exec, &id3);

            pthread_create(&thread4, nullptr, thread_exec, &id4);

            // Aguarda a finalização da thread antes do processo encerrar
            pthread_join(thread3, nullptr);

            pthread_join(thread4, nullptr);

            cout << "Fim do processo filho 2!" << endl;
            return 0;
        } else {
            cout << "Processo pai esperando os filhos terminarem..." << endl;

            wait(NULL);
            wait(NULL);

            cout << "Processo pai terminou!" << endl;
        }
    }
}