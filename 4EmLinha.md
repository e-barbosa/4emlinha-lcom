Esta página apresenta um pequeno resumo do que será o nosso trabalho e o planeamento temporal do mesmo.

## Resumo ##

O nosso projecto basear-se-á no jogo do quatro em linha, cujo objectivo é que um jogador introduza fichas num tabuleiro de modo a que quatro destas formem uma linha na horizontal, vertical, ou na diagonal. O objectivo passa também por impedir que um segundo jogador possa fazer o mesmo. O jogo começará por mostrar um _splash screen_ com música, e daí os jogadores poderão começar a jogar. É apresentado um tabuleiro com o formato de uma tabela, o qual vai sendo preenchido com as fichas dos jogadores, alternando entre os dois, até que um deles ganhe. Para um jogador fazer uma jogada, terá que especificar a coluna do tabuleiro onde quer colocar a sua ficha. Um efeito sonoro será tocado quando for feita uma jogada. No nosso projecto, cada jogador terá um limite de tempo, em segundos, para jogar. Caso não o respeite, o computador seleccionará uma coluna aleatória para jogar.


## Planeamento do Projecto ##

| | **Objectivos** | **Métodos** |
|:|:---------------|:-------------|
| **1ª Semana** |a) Mostrar menu do jogo|void displayMenu();|
|  |b) Criar e mostrar tabuleiro|void createBoard(int lin, int col);|
|  |c) Colocar peças no tabuleiro |void displayBoard(Board);|
|  |  |  |
| **2ª Semana** |a)Criar sprites|Sprite **create\_sprite(char\*pic[.md](.md), char**base);|
|  |b) Animar peças|int animate\_pecas(Sprite **peca, char**base);|
|  |c) Detectar quando as colunas do tabuleiro estão parcialmente ou totalmente preenchidas |bool is\_full(int col);|
|  |  |  |
| **3ª Semana** |a) Contar tempo limite da jogada através do RTC|  |
|  |b) Determinar pontuações dos jogadores|  |
|  |c) Criar splash screen |  |
|  |  |  |
| **4ª Semana** |a) Introduzir musica durante o jogo usando interrupções do RTC|  |
|  |b) Implementar efeitos sonoros|  |
|  |c) Implementar jogo usando porto série |  |