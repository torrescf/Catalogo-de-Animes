#include <iostream>
#include <fstream>
using namespace std;

struct Catalogo{
	int numeracao;
	string nome;
	int numTemporadas;
	int numEpisodios;
	int anoLancamento;
	int anoFinalizacao;
	string generoPrincipal;
	string status;

	    // Função para escrever o catalogo em um arquivo binário 
    void escreverEmArquivoBinario(ofstream& arquivo) const {
        arquivo.write(reinterpret_cast<const char*>(&numeracao), sizeof(numeracao));
        size_t tamanhoNome = nome.size();
        arquivo.write(reinterpret_cast<const char*>(&tamanhoNome), sizeof(tamanhoNome));
        arquivo.write(nome.c_str(), tamanhoNome);
        arquivo.write(reinterpret_cast<const char*>(&numTemporadas), sizeof(numTemporadas));
        arquivo.write(reinterpret_cast<const char*>(&numEpisodios), sizeof(numEpisodios));
        arquivo.write(reinterpret_cast<const char*>(&anoLancamento), sizeof(anoLancamento));
        arquivo.write(reinterpret_cast<const char*>(&anoFinalizacao), sizeof(anoFinalizacao));
        size_t tamanhoGenero = generoPrincipal.size();
        arquivo.write(reinterpret_cast<const char*>(&tamanhoGenero), sizeof(tamanhoGenero));
        arquivo.write(generoPrincipal.c_str(), tamanhoGenero);
        size_t tamanhoStatus = status.size();
        arquivo.write(reinterpret_cast<const char*>(&tamanhoStatus), sizeof(tamanhoStatus));
        arquivo.write(status.c_str(), tamanhoStatus);
    }

    // Função para ler o catalogo de um arquivo binário
    void lerDoArquivoBinario(ifstream& arquivo) {
        arquivo.read(reinterpret_cast<char*>(&numeracao), sizeof(numeracao));
        size_t tamanhoNome;
        arquivo.read(reinterpret_cast<char*>(&tamanhoNome), sizeof(tamanhoNome));
        nome.resize(tamanhoNome);
        arquivo.read(&nome[0], tamanhoNome);
        arquivo.read(reinterpret_cast<char*>(&numTemporadas), sizeof(numTemporadas));
        arquivo.read(reinterpret_cast<char*>(&numEpisodios), sizeof(numEpisodios));
        arquivo.read(reinterpret_cast<char*>(&anoLancamento), sizeof(anoLancamento));
        arquivo.read(reinterpret_cast<char*>(&anoFinalizacao), sizeof(anoFinalizacao));
        size_t tamanhoGenero;
        arquivo.read(reinterpret_cast<char*>(&tamanhoGenero), sizeof(tamanhoGenero));
        generoPrincipal.resize(tamanhoGenero);
        arquivo.read(&generoPrincipal[0], tamanhoGenero);
        size_t tamanhoStatus;
        arquivo.read(reinterpret_cast<char*>(&tamanhoStatus), sizeof(tamanhoStatus));
        status.resize(tamanhoStatus);
        arquivo.read(&status[0], tamanhoStatus);
    }
};

	// Função para busca binária pelo nome do anime
int buscaBinariaNome(Catalogo vet[], int tamanho, string nome) {
    int menor = 0;
    int maior = tamanho - 1;

    while (menor <= maior) {
        int media = menor + (maior - menor) / 2;

        // Verifica se o nome do meio é igual ao nome buscado
        if (vet[media].nome == nome)
            return media;

        // Se o nome no meio for menor, ignora a metade esquerda
        if (vet[media].nome < nome)
            menor = media + 1;

        // Se o nome no meio for maior, ignora a metade direita
        else
            maior = media - 1;
    }

    // Retorna -1 se o nome não for encontrado
    return -1;
}

// Função para busca binária pelo ano de lançamento do anime
void buscaBinariaAno(Catalogo vet[], int tamanho, int anoBusca) {
    int menor = 0;
    int maior = tamanho - 1;
    int cont = 0;

    while (menor <= maior) {
        int media = menor + (maior - menor) / 2;

        // Verifica se o ano de lançamento no meio é igual ao ano buscado
        if (vet[media].anoLancamento == anoBusca) {
            // Encontra todos os animes com o mesmo ano de lançamento
            int esquerda = media;
            int direita = media;

            // Expande para a esquerda
            while (esquerda >= 0 && vet[esquerda].anoLancamento == anoBusca) {
                cont++;
                cout << endl;
				cout << "Anime: " << vet[esquerda].nome << "; ";
				cout << "Temporadas: " << vet[esquerda].numTemporadas << "; ";
				cout << "Episodios: " << vet[esquerda].numEpisodios << "; ";
				cout << "Lancamento: " << vet[esquerda].anoLancamento << "; ";
				cout << "Finalizacao: " << vet[esquerda].anoFinalizacao << "; ";
				cout << "Genero: " << vet[esquerda].generoPrincipal << "; ";
				cout << "O anime esta " << vet[esquerda].status << "; ";
                esquerda--;
            }

            // Expande para a direita
            while (direita < tamanho && vet[direita].anoLancamento == anoBusca) {
                if (direita != media) {  // Evita duplicar a impressão do elemento central
                    cont++;
                    cout << endl;
				cout << "Anime: " << vet[direita].nome << "; ";
				cout << "Temporadas: " << vet[direita].numTemporadas << "; ";
				cout << "Episodios: " << vet[direita].numEpisodios << "; ";
				cout << "Lancamento: " << vet[direita].anoLancamento << "; ";
				cout << "Finalizacao: " << vet[direita].anoFinalizacao << "; ";
				cout << "Genero: " << vet[direita].generoPrincipal << "; ";
				cout << "O anime esta" << vet[direita].status << "; ";
                }
                direita++;
            }
            return;  // Sai da função após encontrar e exibir todos os animes com o ano buscado
        }

        // Se o ano no meio for maior, ignora a metade direita (já que é decrescente)
        if (vet[media].anoLancamento > anoBusca) {
            menor = media + 1;
        }
        // Se o ano no meio for menor, ignora a metade esquerda
        else {
            maior = media - 1;
        }
    }

    // Se o contador cont for 0, o ano não foi encontrado
    if (cont == 0) {
        cout << "Ano nao encontrado!" << endl;
    }
}

// Função para trocar dois elementos
void trocar(Catalogo &a, Catalogo &b) {
    Catalogo aux = a;
    a = b;
    b = aux;
}

// Partição do Quick Sort
int particao(Catalogo vet[], int menor, int maior) {
    string aux = vet[maior].nome;
    int i = menor - 1;
    for (int j = menor; j <= maior - 1; j++) {
        if (vet[j].nome < aux) {
            i++;
            trocar(vet[i], vet[j]);
        }
    }
    trocar(vet[i + 1], vet[maior]);
    return (i + 1);
}

// Função Quick Sort
void quickSortNome(Catalogo vet[], int menor, int maior) {
    if (menor < maior) {
        int pivo = particao(vet, menor, maior);

        quickSortNome(vet, menor, pivo - 1);
        quickSortNome(vet, pivo + 1, maior);
    }
}

// Partição do Quick Sort para ordenar pelo ano de lançamento (decrescente)
int particaoPorAnoLancamento(Catalogo vet[], int menor, int maior) {
    int pivo = vet[maior].anoLancamento;  
    int i = menor - 1;

    for (int j = menor; j <= maior - 1; j++) {
        if (vet[j].anoLancamento > pivo) { 
            i++;
            trocar(vet[i], vet[j]);
        }
    }
    trocar(vet[i + 1], vet[maior]);
    return (i + 1);
}

// Função Quick Sort para ordenar pelo ano de lançamento
void quickSortAno(Catalogo vet[], int menor, int maior) {
    if (menor < maior) {
        int pivo = particaoPorAnoLancamento(vet, menor, maior);
        quickSortAno(vet, menor, pivo - 1);
        quickSortAno(vet, pivo + 1, maior);
    }
}
int main () {
	int tamanho=40;
	Catalogo *anime= new Catalogo[tamanho];
	
	ifstream entrada ("lista.csv");
	//Preenchendo o "vetor anime" com os dados fornecidos pelo arquivo "lista.csv"
	 if (entrada) {
        string linha;
        getline(entrada, linha); 
        getline(entrada, linha);// Lê e descarta a primeira linha (cabeçalho)
	}
	    int contador=0;
	    char delimitador = ';';
	    char delimitador2= '"';
	    string lixo;
	    while(entrada && contador < tamanho){
			  
			  entrada >> anime[contador].numeracao;
			  getline(entrada , lixo , delimitador);
			  getline(entrada , lixo , delimitador2);
			  
		      getline(entrada,anime[contador].nome, delimitador2);
		      getline(entrada , lixo , delimitador);
		      
		      entrada >> anime[contador].numTemporadas;
		      
		      getline(entrada , lixo , delimitador);
		      entrada >> anime[contador].numEpisodios;
		      
		      getline(entrada , lixo , delimitador);
		      entrada >> anime[contador].anoLancamento;
		      
		      getline(entrada , lixo , delimitador);
		      entrada >> anime[contador].anoFinalizacao;
		      
		      getline(entrada , lixo , delimitador);
		      getline(entrada , lixo , delimitador2);
		      getline(entrada , anime[contador].generoPrincipal , delimitador2);
		      
		      getline(entrada , lixo , delimitador);
		      getline(entrada , lixo , delimitador2);
		      getline(entrada , anime[contador].status , delimitador2);
		      contador++;
		      
		  //Se o contador chegar ao tamanho do vetor anime, será necessário redimensionar o vetor anime
		      if(contador==tamanho){
		         int tamanhoNovo = tamanho+5;
			     Catalogo *vetorAux= new Catalogo[tamanhoNovo];
		         //Preenchendo o vetorAux com os valores do vetor anime
		         for(int i=0; i<tamanho; i++){
				     vetorAux[i]=anime[i];
			     }
			         //direcionar o vetor anime para o vetorAux redimensionado
			         delete[] anime;
			         anime = vetorAux;
			         tamanho = tamanhoNovo;
		      }
	     }
	tamanho= contador-1; // correção do tamanho

	quickSortNome(anime, 0, tamanho - 1);
	
	int resposta=0;
	while (resposta != 5) {
    cout << endl << "                                           CATALOGO DE ANIMES                                              " << endl;
    cout << endl << "O que deseja fazer, usuario?" << endl;
    cout << "1) Mostrar um Intervalo de animes" << endl;
    cout << "2) Buscar animes por algum filtro" << endl;
    cout << "3) Sobrescrever/Escrever dados" << endl;
    cout << "4) Remover Dados" << endl;
    cout << "5) Encerrar o Programa" << endl;
    cout << "Resposta (1 ate 5): ";	     
		cin >> resposta; //resposta sobre o que sera feito pelo programa
if (resposta == 1) { // Mostrar um Intervalo
        cout << endl << "Deseja ver todo o catalogo?" << endl;
        cout << "1) Todo o catalogo" << endl;
        cout << "2) Selecionar o intervalo" << endl;
        int resposta1;
        cin >> resposta1;
        
        if (resposta1 == 1) {
            cout << "Deseja ver em ordem alfabetica, genero ou ultimos lancamentos?" << endl;
            cout << "1) Alfabetica" << endl;
            cout << "2) Ultimos lancamentos" << endl;
            cout << "3) Genero" << endl;
            int resposta2;
            cin >> resposta2;
if (resposta2 == 1) {
                quickSortNome(anime, 0, tamanho - 1);
				for (int i = 0; i < tamanho-1; i++) {
                cout << "Anime: " << anime[i].nome << "; ";
                cout << "Temporadas: " << anime[i].numTemporadas << "; ";
                cout << "Episodios: " << anime[i].numEpisodios << "; ";
                cout << "Lancamento: " << anime[i].anoLancamento << "; ";
                cout << "Finalizacao: " << anime[i].anoFinalizacao << "; ";
                cout << "Genero: " << anime[i].generoPrincipal << "; ";
                cout << "Status: " << anime[i].status << endl;
            }} else if (resposta2 == 2) {
                quickSortAno(anime, 0, tamanho - 1);
					for(int i=0; i<tamanho-2 ; i++){
						cout << endl;
						cout << "Anime: " << anime[i].nome << "; ";
						cout << "Temporadas: " << anime[i].numTemporadas << "; ";
						cout << "Episodios: " << anime[i].numEpisodios << "; ";
						cout << "Lancamento: " << anime[i].anoLancamento << "; ";
						cout << "Finalizacao: " << anime[i].anoFinalizacao << "; ";
						cout << "Genero: " << anime[i].generoPrincipal << "; ";
						cout << "O anime esta" << anime[i].status << "; ";
						cout << endl;
					}
				}else if (resposta2 == 3) {
                cout << "Qual genero?" << endl;
                cout << "1) Acao" << endl;
                cout << "2) Drama" << endl;
                cout << "3) Romance" << endl;
                cout << "4) Comedia" << endl;
                cout << "5) Corrida" << endl;
                cout << "6) Esporte" << endl;
                cout << "7) Aventura" << endl;
                int numeroGenero;
                cin >> numeroGenero;
                string genero;
                switch (numeroGenero) {
                    case 1: genero = "Acao"; break;
                    case 2: genero = "Drama"; break;
                    case 3: genero = "Romance"; break;
                    case 4: genero = "Comedia"; break;
                    case 5: genero = "Corrida"; break;
                    case 6: genero = "Esporte"; break;
                    case 7: genero = "Aventura"; break;
                    default: cout << "Genero invalido!" << endl; continue;
                } 
				
				for (int i = 0; i < tamanho; i++) {
                    if (anime[i].generoPrincipal == genero) {
                        cout << "Anime: " << anime[i].nome << "; ";
                        cout << "Temporadas: " << anime[i].numTemporadas << "; ";
                        cout << "Episodios: " << anime[i].numEpisodios << "; ";
                        cout << "Lancamento: " << anime[i].anoLancamento << "; ";
                        cout << "Finalizacao: " << anime[i].anoFinalizacao << "; ";
                        cout << "Genero: " << anime[i].generoPrincipal << "; ";
                        cout << "Status: " << anime[i].status << endl;
                    }
                }
				}else{
					cout << "RESPOSTA INVALIDA, retornando ao comeco do codigo!" << endl;
				}
		}else if(resposta1==2){ //mostrar um certo intervalo informado pelo usuário
			cout << "Insira o intervalo desejado (2 valores): " << endl;
			cout << "Valor Minimo = 0 e Valor Maximo= " << contador << endl;
			int intervaloInicial,intervaloFinal; //inserindo os valores do intervalo desejado
			cin >> intervaloInicial >> intervaloFinal;
			if(intervaloInicial!=intervaloFinal and intervaloInicial>=0 and intervaloInicial<contador and intervaloFinal>intervaloInicial and intervaloFinal<contador){ // limitar os valores possiveis de serem inseridos
			cout << "Deseja ver em ordem Alfabetica ou pelos Ultimos Lancamentos?" << endl << "1) Alfabetica" << endl << "2) Data de Lancamento" << endl;
				int resposta2;
				cin >> resposta2;
					if (resposta2==1){
					quickSortNome(anime, 0, tamanho - 1);
					for(int i=intervaloInicial-1; i<intervaloFinal ;i++){
						cout << endl;
						cout << "Anime: " << anime[i].nome << "; ";
						cout << "Temporadas: " << anime[i].numTemporadas << "; ";
						cout << "Episodios: " << anime[i].numEpisodios << "; ";
						cout << "Lancamento: " << anime[i].anoLancamento << "; ";
						cout << "Finalizacao: " << anime[i].anoFinalizacao << "; ";
						cout << "Genero: " << anime[i].generoPrincipal << "; ";
						cout << "O anime esta" << anime[i].status << "; ";
						cout << endl;
						 }
					 }else if (resposta2==2){
					quickSortAno(anime, 0, tamanho - 1);
						for(int i=intervaloInicial-1; i<intervaloFinal ;i++){
						cout << endl;
						cout << "Anime: " << anime[i].nome << "; ";
						cout << "Temporadas: " << anime[i].numTemporadas << "; ";
						cout << "Episodios: " << anime[i].numEpisodios << "; ";
						cout << "Lancamento: " << anime[i].anoLancamento << "; ";
						cout << "Finalizacao: " << anime[i].anoFinalizacao << "; ";
						cout << "Genero: " << anime[i].generoPrincipal << "; ";
						cout << "O anime esta" << anime[i].status << "; ";
						cout << endl;
						 }
					 }else{
					cout << "RESPOSTA INVALIDA, retornando ao comeco do codigo!" << endl;
					}
				 }else if(intervaloInicial==intervaloFinal){ // se houver apenas 1 item que deseja ver do catálogo
						cout << endl;
						cout << "Anime: " << anime[intervaloInicial].nome << "; ";
						cout << "Temporadas: " << anime[intervaloInicial].numTemporadas << "; ";
						cout << "Episodios: " << anime[intervaloInicial].numEpisodios << "; ";
						cout << "Lancamento: " << anime[intervaloInicial].anoLancamento << "; ";
						cout << "Finalizacao: " << anime[intervaloInicial].anoFinalizacao << "; ";
						cout << "Genero: " << anime[intervaloInicial].generoPrincipal << "; ";
						cout << "O anime esta" << anime[intervaloInicial].status << "; ";
						cout << endl;
					 }else{
						 cout << "Intervalo invalido, retornando ao comeco do codigo!" << endl;
						 }
			 }else{
				 cout << "Valor inserido INVALIDO!, retornando ao comeco do codigo!" << endl;
				 }
			 }else if(resposta==2){ //filtar os animes 
				 cout << "Deseja fazer a buscar por qual tipo de filtro? " << endl;
				 cout << "1) Nome " << endl << "2) Ano de Lancamento" << endl;
				 int resposta2=0;
				 cout << "Resposta(1 ate 2): " ;
				 cin >> resposta2;
				 if(resposta2==1){ // filtrar por nome
					cout << "Insira o nome do Anime desejado: " << endl << "Anime: ";
					string nomeAnime;
					cin.ignore();
					getline(cin,nomeAnime);
					int posAnimeDesejado;
					posAnimeDesejado = buscaBinariaNome(anime, tamanho, nomeAnime);
					if(posAnimeDesejado!=-1){
						cout << endl;
					    cout << "Anime: " << anime[posAnimeDesejado].nome << " ";
					    cout << "Temporadas: " << anime[posAnimeDesejado].numTemporadas << "; ";
					    cout << "Episodios: " << anime[posAnimeDesejado].numEpisodios << "; ";
					    cout << "Lancamento: " << anime[posAnimeDesejado].anoLancamento << "; ";
					    cout << "Finalizacao: " << anime[posAnimeDesejado].anoFinalizacao << "; ";
					    cout << "Genero: " << anime[posAnimeDesejado].generoPrincipal << "; ";
					    cout << "O anime esta" << anime[posAnimeDesejado].status << endl << " ";
					    cout << endl;
					}else{
						cout << "Nome nao encontrado no catalogo!, retornando ao comeco do codigo!" << endl;
				    }
				}else if(resposta2==2){ // filtrar por ano de lançamento
					quickSortAno(anime,0,tamanho-1);
					cout << "Insira o ano de lancamento que desejada: " << endl;
					int anoBusca;
					cin>>anoBusca;
					buscaBinariaAno(anime, tamanho, anoBusca);
				}else{
					cout<< "Valor inserido INVALIDO! Retornando ao comeco do codigo!" << endl;
				}
			}else if(resposta==3){ // Sobrescrever/Escrever dados
					 cout << "1)Escrever dados" << endl << "2)Sobrescrevrer dados " << endl;
					 int resposta3=0;
					 cout << "Resposta (1 ou 2): ";
					 cin >> resposta3;
					     if(resposta3==1){ // deseja escrever novos dados no final do catálogo
						 cout << "Quantos novos dados deseja escrever?" << endl;
						 int respostaE=0;
						 cin >> respostaE;
						 int tamanhoAntigo = tamanho; // para fins de preencher as novas posições é necessário saber o tamanho antigo do catálogo
						 int tamanhoNovo = tamanho+respostaE;
						 
			             Catalogo *vetorAux2= new Catalogo[tamanhoNovo];
		                 //Preenchendo o vetorAux2 com os valores do catálogo
		                 for(int i=0; i<tamanho; i++){
				         vetorAux2[i]=anime[i];
			             }
			             delete[] anime;
			             anime = vetorAux2;
			             tamanho = tamanhoNovo;
			             int contadorE =tamanhoAntigo+1;
						 if(respostaE==1){
							 cout << "Insira os dados do anime: " << endl;
							 }else{
			                  cout << "Insira os dados dos " << respostaE << ": "<< endl;
							  }
						 for(int i=tamanhoAntigo; i<tamanho ; i++){
							 cin.ignore();
							 cout << endl<< "Nome: ";
							 getline(cin,anime[i].nome);
							 cout << endl << "Numero de Temporadas: ";
							 cin >> anime[i].numTemporadas;
							 cout << endl << "Numero de Episodios: ";
							 cin >> anime[i].numEpisodios;
							 cout << endl << "Ano de Lancamento: ";
							 cin >> anime[i].anoLancamento;
							 cout << endl << "Ano Finalizacao: "; 
							 cin >> anime[i].anoFinalizacao;
							 cin.ignore();
							 cout << endl << "Genero Principal: ";
							 getline(cin,anime[i].generoPrincipal);
							 cout << endl << "Status: ";
							 getline(cin,anime[i].status);
							 contadorE++;
					     }
						 cout << "Deseja salvar as alteracoes feitas?" << endl;
						 cout << "1)Sim" << endl << "2)Nao" << endl;
						 int respostaE1=0;
						 cout << "Resposta (1 ou 2): ";
						 cin >> respostaE1;
						 
						 if(respostaE1==1){ //deseja salvar as alterações
						   ofstream saida ("lista.csv");
				           int contadorE2=0;// contador para saber quando deverá parar de escrever dados na saída
				           saida << "# Numeracao Nome Número_Temporadas Número_Episódios Ano_Lançamento Ano_Finalização Gênero_Principal Status" << endl;
				           saida << "OBS:(anoFinalizacao=0 sera quando o anime ainda nao estiver finalizado)" << endl;
				           while(contadorE2<tamanho){
							     saida << anime[contadorE2].numeracao << " ";
								 saida << anime[contadorE2].nome << " ";
								 saida << anime[contadorE2].numTemporadas << " ";
							     saida << anime[contadorE2].numEpisodios << " ";
								 saida << anime[contadorE2].anoLancamento << " ";
							     saida << anime[contadorE2].anoFinalizacao << " ";
								 saida << anime[contadorE2].generoPrincipal	<< " ";									    
							     saida << anime[contadorE2].status << " ";
								 saida << endl;
								 contadorE2++;
						  }
							 
						  cout << "Catalogo atualizado com sucesso acima!" << endl; 
						  }else if(respostaE1==2){ // não deseja salvar as alterações = redimensionar o vetor para o tamanho antigo, excluíndo os novos dados
							      tamanhoNovo= tamanho-respostaE;
							      Catalogo *vetorAux2= new Catalogo[tamanhoNovo];
		                          for(int i=0; i<tamanhoNovo; i++){
				                  vetorAux2[i]=anime[i];
			                      }
			                      delete[] anime;
			                      anime = vetorAux2;
			                      tamanho = tamanhoNovo;
							      cout << "Resposta nao salva, catalogo retornando ao antigo!" << endl;
						}
						
					 }else if(resposta3==2){ // usuário deseja sobrescrever dados já existentes no catálogo
						 cout << endl << "Qual numeracao do catalogo deseja sobrescrever? " << endl;
						 int numeracaoDesejada=0;
						 cout << "Resposta: (1 ate " << tamanho-2 << ")" << endl; 
						 cin >> numeracaoDesejada;
						 cout << "Insira os dados anime: " << endl;
						 //declarando as variáveis que vão armazanar os dados escritos pelo usuário para sobrescrever os já existentes
						 string nomeAux;
						 int numTemporadasAux;
						 int numEpisodiosAux;
						 int anoLancamentoAux;
						 int anoFinalizacaoAux;
						 string generoPrincipalAux;
						 string statusAux;
						 cout << "Nome: ";
						 cin.ignore();
						 getline(cin,nomeAux);
						 cout << endl << "Numero de Temporadas: ";
						 cin >> numTemporadasAux;
						 cout << endl << "Numero de Episodios: ";
						 cin >> numEpisodiosAux;
						 cout << endl << "Ano de Lancamento: ";
						 cin >> anoLancamentoAux;
						 cout << endl << "Ano Finalizacao: ";
						 cin >> anoFinalizacaoAux;
						 cout << endl << "Genero Principal: ";
						 cin.ignore();
						 getline(cin,generoPrincipalAux);
						  cout << endl << "Status: ";
						 cin.ignore();
						 getline(cin,statusAux);
						 int respostaS=0;
						 cout << endl << "Deseja salvar as alteracoes?" << endl;
						 cout << "1)Sim" << endl << "2)Nao" << endl;
						 cout << "Resposta(1 ou 2): ";
						 cin >> respostaS; // resposta Sobrescrever
						 if(respostaS==1){ //deseja salvar as alteracoes
						 for(int i=0; i<tamanho; i++){
							 if(anime[i].numeracao==numeracaoDesejada){
								 anime[i].nome=nomeAux;
								 anime[i].numTemporadas=numTemporadasAux;
								 anime[i].numEpisodios=numEpisodiosAux;
								 anime[i].anoLancamento=anoLancamentoAux;
								 anime[i].anoFinalizacao=anoFinalizacaoAux;
								 anime[i].generoPrincipal=generoPrincipalAux;
								 anime[i].status=statusAux;
								 int contadorS=0;
								 ofstream saida ("lista.csv");
								 saida << "# Numeracao Nome Número_Temporadas Número_Episódios Ano_Lançamento Ano_Finalização Gênero_Principal Status" << endl;
								 saida << "OBS:(anoFinalizacao=0 sera quando o anime ainda nao estiver finalizado)" << endl;
								 while(contadorS<tamanho-2){
									 saida << anime[contadorS].numeracao << " ";
									 saida << anime[contadorS].nome << " ";
								 	 saida << anime[contadorS].numTemporadas << " ";
							     	 saida << anime[contadorS].numEpisodios << " ";
								 	 saida << anime[contadorS].anoLancamento << " ";
							     	 saida << anime[contadorS].anoFinalizacao << " ";
								 	 saida << anime[contadorS].generoPrincipal	<< " ";									    
							     	 saida << anime[contadorS].status << " ";
								 	 saida << endl;
								 	 contadorS++;
									 }
								 
								 }
						 }
						 cout << "Valores Atualizados com Sucesso!"	 << endl;
					     }else if(respostaS==2){ //nao deseja salvar as alteracoes
							      cout << "Resposta nao salva, catalogo retornando ao antigo!" << endl;
						  }
						 
					 }
				 
				}	 
				else if(resposta==4){ // Remover Dados
					    cout << "Qual a posicao do catalogo que deseja remover?" << endl;
					    cout << "Resposta (1 ate " << tamanho << "): ";
					    int respostaRemover=0;
					    cin >> respostaRemover;
		
					    cout << "Deseja salvar as alteracoes?"<< endl;
					    cout << "1)Sim " << endl << "2)Nao" << endl;
					    cout << "Resposta(1 ou 2):";
					    int respostaRemover2=0;
					    cin >> respostaRemover2;
					    if(respostaRemover2==1){
						   int novoTamanho=tamanho-1; // novo tamanho do catalogo removendo um anime dele
		    			   Catalogo *auxRemover = new Catalogo[novoTamanho];
		    			   int contadorRemover=0;
		    			   for(int i=0; i<novoTamanho ;i++){
			    			   if(anime[i].numeracao != respostaRemover){
				   			   auxRemover[contadorRemover]=anime[i];
				   			   contadorRemover++;
			    			   }
		    			   }
		    			   for(int i=respostaRemover-1; i<novoTamanho; i++){
			   			    auxRemover[i].numeracao -=1;
		    			   }
		    			   delete[] anime;
		    			   tamanho = novoTamanho; 
		    			   anime = auxRemover;
		    			   ofstream saida ("lista.csv");
						   int contadorR2=0;
						   saida << "# Numeracao Nome Número_Temporadas Número_Episódios Ano_Lançamento Ano_Finalização Gênero_Principal Status" << endl;
						   saida << "OBS:(anoFinalizacao=0 sera quando o anime ainda nao estiver finalizado)" << endl;
						   char aux1 = ';';
						   char aux2 = '"';
						   while(contadorR2<tamanho-1){
				  			     saida << anime[contadorR2].numeracao << aux1 << aux2;
				  			     saida << anime[contadorR2].nome << aux2 << aux1;
				 			     saida << anime[contadorR2].numTemporadas << aux1;
				  			     saida << anime[contadorR2].numEpisodios << aux1;
				  			     saida << anime[contadorR2].anoLancamento << aux1;
				  			     saida << anime[contadorR2].anoFinalizacao << aux1 << aux2;
				  			     saida << anime[contadorR2].generoPrincipal << aux2 << aux1 << aux2;									    
				  			     saida << anime[contadorR2].status << aux2;
				  			     saida << endl;
				  			     contadorR2++;
						  }
						  
						   cout << "Catalogo atualizado com sucesso, retornando ao comeco do codigo!" << endl;
		    
					   }else if(respostaRemover2==2){
				                cout << "Alteracoes nao salvas, retornando ao comeco do codigo!" << endl;
					    }else{
					         cout << "Resposta invalida, retornando ao comeco do codigo!" << endl;
					     }
						
			    }
}if(resposta==5){
	cout << endl << "Programa Encerrado!" << endl;
	}else if(resposta>5){
		     cout << "RESPOSTA INVALIDA, retornando ao comeco do codigo!" << endl;
	 }
 return 0;
}
