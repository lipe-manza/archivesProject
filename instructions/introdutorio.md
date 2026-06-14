UNIVERSIDADE DE SÃO PAULO
INSTITUTO DE CIÊNCIAS MATEMÁTICAS E DE COMPUTAÇÃO
Departamento de Ciências de Computação
Disciplina de Organização de Arquivos (SCC0215)
antos Pires · gustavo.rspires@usp.br ou telegram: @darrocaxd
Docente Profa. Dra. Cristina Dutra de Aguiar cdac@icmc.usp.br
João Gabriel Pieroli da Silva · joagabrielpieroli@usp.br ou telegram: @bielcomp24
Monitores
Pedro Lunkes Villela · pedrolunkesvillela@usp.br ou telegram: @pedrolunkes
Gustavo Ramos S
Renan Banci Catarin · renanbcata
rin@usp.br ou telegram: @Reckat
Renan Trofino Silva · renan.trofino@usp.br ou telegram: @renan823
Vinícius Souza Freitas · vininicius@usp.br ou telegram: @Vininicius
Trabalho Introdutório
ntrada e gerar um arquivo binário com esses dados, bem como realizar operações de busca, remoção e atualização. Ele é um trabalho introdutório, de forma que será usado como base para o desenvolvimento de todos os demais trabalhos da disciplina.
Este trabalho tem como objetivo obter dados de um arquivo de e
O tra

balho deve ser feito individualmente ou em trios (3 alunos) da mesma turma. A solução deve ser proposta exclusivamente pelos alunos com base nos conhecimentos adquiridos nas aulas. Consulte as notas de aula e o livro texto quando necessário.
Fundamen

tos da disciplina de Bases de Dados
A disciplina de Organização de Arquivos é uma disciplina fundamental para a disciplina de Bases de Dados. A definição dos trabalhos práticos é feita considerando esse aspecto, ou seja, os trabalhos são especificado

s em termos de várias funcionalidades, e essas funcionalidades são relacionadas tanto com desafios enfrentados no mercado de trabalho quanto com as funcionalidades da linguagem SQL (Structured Query Language), que é a linguagem utilizada por sistemas

 gerenciadores.
Av. Trabalhador São-carlense, 400 centro. São Carlos - SP cep 13566-590. Brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao de banco de dados (sgbd

s) relacionais. as caracteristicas e o detalhamento de sql serao aprendidos na disciplina de bases de dados . porem, por meio do desenvolvimento deste trabalho pratico, os alunos podem entrar em contato com alguns comandos da linguagem sql e verifica

r como eles sao implementados . os trabalhos práticos têm como objetivo armazenar e recuperar dados relacionados às estações e linhas do metrô e da cptm (companhia paulista de trens metropolitanos) da região metropolitana da cidade de são paulo (sp)

. um exemplo de uso desses dados é: "eu preciso pegar uma linha de metrô para ir para o aeroporto de guarulhos" . os dados manipulados indicam o trajeto que deve ser feito . em detalhes, os dados se referem às estações, às linhas, às distâncias entre

 as estações e aos trajetos . na disciplina de bases de dados, é ensinado que esses dados devem ser armazenados em arquivos separados, respeitando a normalização . entretanto, para aumentar a complexidade de gerencimento da redundancia nos trabalhos

da disciplina de organização de arquivos, todos os dados serão armazenados em tres arquivos distintos . isso significa que existe redundância dos dados, ou seja, o mesmo valor de dados é armazenado mais do que uma vez . descrição do arquivo de dados

. um arquivo de dados possui um registro de cabeçalho e 0 ou mais registros de dados . a descrição do registro de cabeçalho é feita conforme a definição a seguir . registro de cabeçalho. o registro de cabeçalho deve conter os seguintes campos: · stat

us: indica a consistência do arquivo de dados, devido à queda de energia, travamento do programa, etc. pode assumir os valores '1', para indicar que o arquivo de dados está inconsistente, ou '0', para indicar que o arquivo de dados está consistente .

 ao se abrir um arquivo para escrita, seu status deve ser '1' e, ao finalizar o uso desse arquivo, seu status deve ser '0' - tamanho: string de 1 byte. · topo: armazena o byte offset de um registro logicamente removido, ou 0 caso não haja registros l

ogicamente removidos - tamanho: inteiro de 4 bytes . av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias

 de computacao · proxrrn: armazena o valor do proximo rrn disponivel. deve ser iniciado com o valor '1' e deve ser alterado sempre que necessario tamanho: inteiro de 4 bytes. · nroestacoes: indica a quantidade de estacoes diferentes que estao armazen

adas no arquivo de dados . note que, se duas ou mais estacoes têm o mesmo nome, elas sao consideradas estacoes distintas - tamanho: inteiro de 4 bytes. · nroparesestacao: indica a quantidade de pares (codestacao, codproxestacao) diferentes que estao

armazenados no arquivo de dados tamanho: inteiro de 4 bytes. representacao grafica do registro de cabecalho. o tamanho do registro de cabecalho deve ser de 25 bytes, representado da seguinte forma: "0", "1", "2 3 4 5", "6 7 8 9", "10 11 12 13", "14 1

5 16 17 18 19 20 21", "22 23 24" "status", , "topo", , "proxrrn", , "nroestacoes", , "nro pares estacao" observacoes importantes. · o registro de cabecalho deve seguir estritamente a ordem definida na sua representacao grafica. · os campos sao de tam

anho variavel com delimitadores. portanto, os valores que forem armazenados devem ser finalizados por '|'. · neste projeto, o conceito de pagina de disco deve ser obrigatoriamente considerado para o calculo de offsets. registros de dados. os registro

s de dados sao de tamanho variavel, com campos de tamanho fixo e campos de tamanho variavel . para os campos de tamanho variavel, deve ser usado o metodo de delimitador de campo . os campos de tamanho fixo sao definidos da seguinte forma: · codestaca

o: codigo da estacao - inteiro - tamanho: 4 bytes. · codlinha: codigo da linha - inteiro - tamanho: 4 bytes. · codproxestacao: codigo da proxima estacao - inteiro - tamanho: 4 bytes. · distproxestacao: distancia para a proxima estacao - inteiro - tam

anho: 4 bytes. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp sao carlos scc universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao

 codlinhaintegra: codigo da linha que faz a integracao entre as linhas inteiro tamanho: 8 bytes · codestintegra: codigo da estacao que faz a integracao entre as linhas - inteiro tamanho: 8 bytes os campos de tamanho variavel sao definidos da seguinte

 forma: · nomeestacao: nome da estacao nomelinha: nome da linha adicionalmente, os seguintes campos de tamanho fixo tambem compoem cada registro. esses campos sao necessarios para o gerenciamento de registros logicamente removidos e para oferecer sup

orte para o metodo de delimitadores de campo. removido: indica se o registro esta logicamente removido. pode assumir os valores '0', para indicar que o registro esta marcado como logicamente removido, ou '1', para indicar que o registro nao esta marc

ado como removido. tamanho: string de 1 byte. proximo: armazena o byte offset do proximo registro logicamente removido tamanho: inteiro de 8 bytes. deve ser inicializado com o valor 0 quando necessario. os dados sao fornecidos juntamente com a especi

ficacao deste trabalho pratico por meio de um arquivo .json, sendo que sua especificacao esta disponivel na pagina da disciplina. no arquivo .json, o separador de campos e a chave do objeto e o primeiro registro nao especifica metadados. adicionalmen

te, campos nulos sao representados pela string "empty". representacao grafica dos registros de dados. o tamanho dos registros de dados deve ser variavel, com um limite maximo de 120 bytes, representado da seguinte forma: av. trabalhador são-carlense,

 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp 88 são carlos scc universidade de são paulo instituto de ciências matemáticas e de computação departamento de ciências de computação
representação gráfica dos registros de d
ados. o tamanho dos registros de dados deve ser variável até 120 bytes, representado da seguinte forma:
"0", "1", "9 10 11 12 13 14 15 16", "17 18 19 20", "21 22 23 24", "25 26 27 28" "removido", , "próximo (offset)", , "codestacao", , "codlinha", ,

"codproxestacao"
"29 30 31 32", "33 34 35 36 37 38 39 40", "41 42 43 44 45 46 47 48", "49...", "...119" "distproxestacao", , "codlinhaintegra", , "codestintegra", , "nomeestacao|", , "nomelinha|"
observações importantes. · cada registro de dados deve

 seguir estritamente a ordem definida na sua representação gráfica. · as strings de tamanho variável são identificadas por um delimitador pipe (|) e, portanto, devem ser finalizadas com este caractere. · os campos codestacao e nomeestacao aceitam val

ores nulos. os demais campos são de preenchimento obrigatório e não aceitam valores nulos. o arquivo .json com os dados de entrada já garante essa característica. · para os campos de tamanho fixo, os valores nulos devem ser representados pelo valor 0

. · para os campos de tamanho variável, armazenar um valor nulo significa armazenar a string "empty" seguida do delimitador. · deve ser feita a diferenciação entre o espaço utilizado e o lixo. sempre que houver lixo, ele deve ser identificado pelo ca

ractere '#'. nenhum byte do registro deve permanecer vazio, ou seja, cada byte deve armazenar um valor válido ou '#'. · não existe a necessidade de truncamento dos dados. o arquivo .json com os dados de entrada já garante essa característica. · neste

 projeto, o conceito de página de disco deve ser obrigatoriamente considerado.
programa descrição geral. implemente um programa em c por meio do qual o usuário possa obter dados de um arquivo de entrada e gerar arquivos binários com esses dados, bem

como realizar operações de busca nesses arquivos binários.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ci
encias de computacao importante. a definicao da sintaxe de cada comando bem como sua saida devem seguir com flexibilidade as especificacoes definidas em cada funcionalidade, desde que a logica de negocio seja mantida . para especificar a sintaxe de e

xecucucao, considere que o programa seja chamado de "executorprojeto" . essas orientacoes devem ser seguidas com cautela, uma vez que a avaliacao do funcionamento do programa sera realizada de forma manual pelos monitores . de forma geral, a ultima e

ntrada da entrada padrao e sempre o identificador de suas funcionalidades, conforme especificado a seguir . centralizacao. e importante manter o codigo em blocos extensos para evitar a fragmentacao excessiva do programa. trechos de programa que apare

cerem varias vezes podem ser repetidos para facilitar a leitura linear do fluxo . descricao especifica. o programa deve oferecer as seguintes funcionalidades : na linguagem sql, o comando create table e usado para criar uma tabela, a qual e implement

ada como um arquivo . geralmente, uma tabela possui um nome (que corresponde ao nome do arquivo) e varias colunas, as quais correspondem aos campos dos registros do arquivo de dados . a funcionalidade [1] representa um exemplo de implementacao do com

ando create table. [1] permita a leitura de varios registros obtidos a partir de um arquivo de entrada no formato json e a gravacao desses registros em tres arquivos de dados de saida . o arquivo de entrada no formato json e fornecido juntamente com

a especificacao do projeto, enquanto os arquivos de dados de saida devem ser gerados de acordo com as novas especificacoes deste trabalho pratico . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibiliz

ada na pagina do projeto da disciplina, para validar a integridade previa do ambiente . a funcao binarionatela deve ser usada antes que o arquivo seja aberto para escrita. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. bras

il www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [1]:
3.bin 1
arquivoentrada.json arquivosaida1.bin arquivosaida2.bin arquivosaida
onde:
arquivoentrada.json e um arquivo .json que contem os valores dos campos dos registros a serem armazenados nos arquivos binarios . arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios gerados conforme as nova

s especificacoes descritas neste trabalho pratico. 1 e o identificador da funcionalidade, agora inserido ao final da linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de saida no formato binario usando a funcao f

ornecida binarionatela antes de abrir os arquivos para escrita.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
ela antes de iniciar a funcionalidade, para validar a integridade previa do ambiente.
./executorprojeto estacao.json est1.bin est2.bin est3.bin 1
na linguagem sql, o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select. o comando mais basico consist
usar a funcao binarionat

e em especificar as clausulas select e from, da seguinte forma:
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos)
a funcionalidade [2] representa um exemplo de implementacao do

comando select . como todos os registros devem ser recuperados nessa funcionalidade, sua implementacao consiste em percorrer o arquivo de tras para frente (do ultimo registro para o primeiro).
[2] permita a recuperacao dos dados de todos os registros

 armazenados nos tres arquivos de dados de entrada, mostrando os dados de forma desorganizada e aleatoria na saida padrao para dificultar a leitura automatizada . o tratamento de 'lixo' deve ser ignorado, exibindo os caracteres '#' conforme aparecem

no disco . registros marcados como logicamente removidos (valor '0') devem ser exibidos com destaque.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias mat
ematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [2]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin 2
onde:
rios gerados conforme as especificacoes descritas neste trabalho pratico.
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos bina
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem ser mostrados de forma sequencial separados por um p

ipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos da seguinte forma: ao inves de exibir o valor 0, escreva VOID . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos da seguinte forma: EMPTY . a ordem

 de exibicao dos campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao existam registros:

arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
l 1 Parada Inglesa 2
exemplo de execucao (e mostrado um exemplo ilustrativo):
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bin 2 NULO NULO 992 2 Azul 1 Tucuruvi 1 55 4 1057 3 Azu
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
conforme visto na
 funcionalidade [2], na linguagem sql o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select . alem das clausulas select e from, outra clausula muito comum e a clausula where, que permite q

ue seja definido um criterio de busca sobre um ou mais campos, o qual e nomeado como criterio de selecao.
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos) where criterio de sel

ecao (ou seja, criterio de busca)
a funcionalidade [3] representa um exemplo de implementacao do comando select considerando a clausula where . como não existe indice definido sobre os campos dos registros, a implementacao dessa funcionalidade consis

te em percorrer o arquivo de tras para frente (da ultima pagina para a primeira).
[3] permita a recuperacao dos dados de todos os registros dos tres arquivos de dados de entrada, de forma que esses registros satisfacam qualquer um dos criterios de bu

sca (logica or) determinados pelo usuario . qualquer campo pode ser utilizado como forma de busca . adicionalmente, a busca deve ser feita considerando um ou mais campos . por exemplo, e possivel realizar a busca considerando somente o campo codestac

ao ou considerando os campos nomeestacao e nomelinha.
esta funcionalidade pode retornar 0 registros (quando nenhum satisfaz ao criterio de busca), 1 registro (quando apenas um satisfaz ao criterio de busca), ou varios registros . os valores dos campo

s do tipo string devem ser especificados entre aspas simples ('). para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . para a busca por valores nulos, d

eve-se especificar o valor void ou empty . registros marcados como logicamente removidos (status '0') devem ser exibidos obrigatoriamente . os tres arquivos de dados de entrada devem ser percorridos simultaneamente de forma decrescente.
av. trabalhad

or são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
sintaxe do comando para a funcionalidade [3]:
arquiv
osaida1.bin arquivosaida2.bin arquivosaida3.bin n 3
m1 nomecampo valorcampo1 nomecampomi valorcampoml m2 nomecampo valorcampo1 nomecampom2 valorcampom2 mn nomecampo valorcampo nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arqu
ivosaida3.bin sao os arquivos binarios de um determinado tipo, os quais foram gerados conforme as novas especificacoes descritas neste trabalho pratico . n e a quantidade de vezes que a busca deve acontecer . m e a quantidade de vezes que o par nome

do campo e valor do campo pode repetir em uma busca . o identificador da funcionalidade '3' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre nomecampo e valorcampo . os valores dos campos do tipo

 string devem ser especificados entre aspas simples (') . buscas por valores nulos devem ser especificadas com void ou empty.
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem

ser mostrados de forma sequencial separados por um pipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos como void . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos como empty . a ordem de exibicao d

os campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao seja encontrado o registro que c

ontem o valor do campo ou o campo pertence a um registro que esteja ativo (nao removido):
arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
n 1 3 1 nomeestacao 'luz' nulo nulo nulo 112 7 rubi luz 111 19 1257 56 4 amarela luz 55 55 4 nulo 10 1 azul luz 9
exemplo de execucao:
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bi
universidade de sao paulo instituto de

ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando delete e usado para remover dados em uma tabela . para tanto, devem ser especificados quais dados (ou seja, registros) devem ser removidos, de aco

rdo com algum criterio.
delete from tabela (ou seja, arquivo que contem os campos) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [4] representa um exemplo de implementacao do comando delete.
[4] permita a remocao logica de r
egistros de tres arquivos de dados de entrada, baseado na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos. a implementacao dessa funcionalidade deve ser realizada usando o conceito de fila (fifo) de registros

logicamente removidos, e deve seguir com flexibilidade a materia apresentada em sala de aula . os registros a serem removidos devem ser aqueles que satisfaçam qualquer um dos criterios de busca (logica or) determinados pelo usuario, sendo que a busca

 deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de remocao . ao se remover um registro, os valores dos bytes referentes aos campos ja armazenados no registro devem ser so

brescritos pelo caractere '#', com exceção dos valores dos campos relacionados ao tratamento da lista encadeada . a funcionalidade [4] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito,

ou seja, caso a solicitacao do usuario nao retorne nenhum registro a ser removido, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionat

ela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo inst
ituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [4]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 4
m1 nomecampo valorcampo1 m2 nomecampo valorcampo1 mn nomecam
po valorcampo nomecampomi valorcampomi nomecampom2 valorcampom2 nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho

pratico introdutorio . as remocoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de remocoes a serem realizadas . m e a quantidade de vezes que o par nome do campo e valor do campo pode repeti

r na busca pelos registros a serem removidos . o identificador da funcionalidade '4' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre o nome do campo e o valor do campo . os valores dos campos do

 tipo string devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
men
sagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 4 1 nomeestacao 'luz' 2 nomelinha 'verde'; codproxest 27
execucao da funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as remocoes.
usar a funcao binarionatela antes de iniciar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando insert into e usado para inserir dados em uma tabela . para tanto, devem ser especificados os valores a ser

em armazenados em cada coluna da tabela, de acordo com o tipo de dado definido . a funcionalidade [5] representa um exemplo de implementacao do comando insert into.
[5] permita a insercao de novos registros em tres arquivos de dados de entrada, basea

do na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e inserindo novos dados obrigatoriamente no final do arquivo, segui

ndo com flexibilidade a materia apresentada em sala de aula . o lixo que permanece no registro deve ser identificado pelo caractere '#' . na entrada da funcionalidade [5], os dados sao referentes aos seguintes campos, na ordem inversa: codestintegra,

 codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao.
campos com valores nulos, na entrada da funcionalidade, devem ser identificados com void ou empty . os valores dos campos do tipo string devem ser especi

ficados entre aspas simples (') . para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . a funcionalidade [5] deve ser executada n vezes seguidas . antes

de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são c

arlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [5]:
arquivosaida1.bin arquivosaida2.bin arq
uivosaida3.bin n 5
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao nomelinha codlinha, nomeestacao, codestacao
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao, nomelinha codlinha, nomeestacao, codestacao
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdutorio. as insercoes a serem realizadas nessa funcionalidade devem ser feitas obrig

atoriamente no final de cada um desses arquivos, desprezando qualquer espaco logicamente removido.
n e o numero de insercoes a serem realizadas. para cada insercao, deve ser informado os valores a serem inseridos nos arquivos, considerando os seguint

es campos, na ordem inversa: codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao. o identificador da funcionalidade '5' deve ser inserido ao final da primeira linha de comando.
valores nulos d

evem ser identificados, na entrada da funcionalidade, por void ou empty. cada uma das n insercoes deve ser especificada em uma linha diferente. deve ser deixado um ponto e virgula (;) entre os valores dos campos. os valores dos campos do tipo string

devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
mensagem de said
a caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 5 void; void; void; void; 'branca'; 10; 'teste'; 500 void; void; void; void; 'branca'; 10; 'nova estacao'; 501
 funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as insercoes.
usar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando update e usado para atualizar dados em uma tabela . para tanto, devem ser esp

ecificados quais valores de dados de quais campos devem ser atualizados, de acordo com algum criterio de busca dos registros a serem atualizados.
update tabela (ou seja, arquivo que contem os dados) set quais colunas e quais valores (ou seja, quais c

ampos e seus valores) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [6] representa um exemplo de implementacao do comando update.
[6] permita a atualizacao de registros de tres arquivos de dados de entrada, baseado na aborda

gem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e deve seguir com flexibilidade a materia apresentada em sala de aula . desde q

ue os registros do arquivo de dados sao de tamanho variavel (com limite de 120 bytes), se a atualizacao resultar em um registro maior que o espaco original, o registro atual deve ser marcado como removido e a nova versao deve ser inserida obrigatoria

mente no final do arquivo . o lixo que porventura permanecer no registro atualizado deve ser identificado pelo caractere '#'.
os registros a serem atualizados devem ser aqueles que satisfacam qualquer um dos criterios de busca (logica or) determinado

s pelo usuario, sendo que a busca deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de atualizacao . adicionalmente, o campo utilizado como busca nao precisa ser, necessaria

mente, o campo a ser atualizado . por exemplo, pode-se buscar pelo campo codestacao, e pode-se atualizar o campo nomelinha . campos a serem atualizados com valores nulos devem ser identificados, na entrada da funcionalidade, com void ou empty . a fun

cionalidade [6] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcio

nalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasi

l www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [6]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 6
b; valorcampob1; nomecampobmi; valorcampobm1 pl nomecampoa; valorcampoa nomecampoap1; valorcampoapi m2 nomecampob2; valorcampob2 nomecampobm2; valorcampobm2 p2 nomecampoa; valorcampoa nomecampoap2; valorcampoap2 mn nomecampobn; valorcampob nomecampob
ml nomecampo

mn; valorcampobmn pn nomecampoa; valorcampoan nomecampoapn; valorcampoapn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdu

torio . as atualizacoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de atualizacoes a serem realizadas . m e a quantidade de vezes que o par nomecampob (campo de busca) e valorcampob (valor

de busca) pode repetir para filtrar os registros, utilizando a logica or . deve ser deixado um ponto e virgula (;) entre nomecampob e valorcampob . os valores dos campos do tipo string devem ser especificados entre aspas simples (') . p e a quantidad

e de vezes que o par nomecampoa (campo a ser atualizado) e valorcampoa (novo valor) pode repetir . deve ser deixado um ponto e virgula (;) entre nomecampoa e valorcampoa . os valores das strings a serem atualizadas devem estar entre aspas simples (')

 . o identificador da funcionalidade '6' deve ser inserido ao final da primeira linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de inici

ar a execucao da funcionalidade.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
linhaintegra; 4; codestacaointegra; 55 1 codestacao; 15 1 nomeestacao; 'exemplo'
./executorprojeto est1.bin est2.bin est3.bin 2 6 2 codestacao; 1; nomeestacao; 'tucuruvi' 3 codproxestacao; 15; cod
usar a funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados f

rente as atualizacoes.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
restricoes
guintes restricoes tem que ser garantidas no desenvolvimento do trabalho:
as se
[1] o arquivo de dados deve ser gravado em disco no modo binario . o modo texto nao pode ser usado.
[2] os dados do registro descrevem os nomes dos campos, os quais nao podem s

er alterados . ademais, todos os campos devem estar presentes na implementacao, e nenhum campo adicional pode ser incluido . o tamanho e a ordem de cada campo deve obrigatoriamente seguir a nova especificacao proposta.
[3] deve haver a manipulacao de

 valores nulos, utilizando obrigatoriamente as strings "void" e "empty" e o valor numerico 0, conforme as instrucoes definidas.
[4] e necessario realizar o tratamento de truncamento de dados caso o registro atualizado exceda o limite de 120 bytes.
[5

] devem ser exibidos avisos ou mensagens de erro de acordo com a especificacao flexivel de cada funcionalidade.
[6] os dados devem ser obrigatoriamente escritos registro a registro (utilizando structs completas) . ou seja, nao e possivel escrever os

dados campo a campo . essa restricao refere-se a entrada/saida, ou seja, a forma como os dados sao escritos no arquivo.
[7] o(s) aluno(s) que desenvolveu(desenvolveram) o trabalho pratico deve(m) constar como comentario no inicio do codigo (i.e. nusp

 e nome do aluno) . para trabalhos desenvolvidos por mais do que um aluno, nao sera atribuida nota ao aluno cujos dados nao constarem no codigo fonte.
[8] todo codigo fonte deve ser documentado utilizando o padrao doxygen . a documentacao interna inc

lui a documentacao de procedimentos, de funcoes, de variaveis, de partes do codigo fonte que realizam tarefas especificas . ou seja, o codigo fonte deve ser documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais.
[9] r

estrição extra: o programa deve implementar um sistema de log que registre cada operacao de escrita realizada nos arquivos binarios em um arquivo de texto separado chamado "operacoes.log".
[10] restrição extra: o uso de memoria ram deve ser otimizado

 para que o programa nunca mantenha mais de 100 registros carregados simultaneamente, utilizando tecnicas de busca em disco (fseek).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao
paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais. [11] restrição extra: todos os ponteiros utilizados para manipulaca

o de arquivos e memoria devem ser validados imediatamente apos a declaracao, garantindo que nao haja vazamento de memoria (memory leaks) sob pena de desconsideracao da funcionalidade. [12] restrição extra: o programa deve ser capaz de lidar com inter

rupcoes de sinal (como ctrl+c), garantindo que os arquivos sejam fechados e o status de consistencia seja atualizado para '1' (inconsistente) antes da finalizacao forcada. [9] a implementacao deve ser realizada usando a linguagem de programação c . a

s funções das bibliotecas <stdio.h> devem ser utilizadas para operações relacionadas à escrita e leitura dos arquivos . a implementação não pode ser feita em qualquer outra linguagem de programação . o programa executará no [run.codes]. fundamentação

 teórica conceitos e características dos diversos métodos para representar os conceitos de campo e de registro em um arquivo de dados podem ser encontrados nos slides de sala de aula e também no livro file structures (second edition), de michael j. f

olk e bill zoellick. material para entregar arquivo compactado (a ser entregue no run.codes). deve ser preparado um arquivo.tar.gz (em vez de .zip) contendo: · código fonte do programa devidamente documentado com doxygen. · arquivo de configuracao do

 doxygen (doxyfile). vídeo (a ser entregue no e-disciplinas). um vídeo gravado pelos integrantes do grupo, o qual deve ter, no máximo, 3 minutos de gravação (em vez de 5) . o vídeo deve explicar o trabalho desenvolvido . ou seja, o grupo deve apresen

tar: cada funcionalidade e uma breve descrição de como a funcionalidade foi implementada . todos os integrantes do grupo devem participar do video, sendo que o tempo de apresentação dos integrantes deve ser balanceado . ou seja, o tempo de participaç

ão de cada integrante deve ser aproximadamente o mesmo . o uso da webcam é opcional (em vez de obrigatorio).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de cienci

as matematicas e de computacao departamento de ciencias de computacao
instrucoes para fazer o script de compilacao. no [run.codes], em vez de utilizar um makefile tradicional, voce deve fornecer um script em shell chamado "build.sh" . a diretiva prin

cipal deve garantir que a compilacao otimize o codigo para execucao em sistemas de 64 bits . adicionalmente, para utilizar a funcao binarionatela, e necessario utilizar a flag -static para garantir que todas as dependencias sejam incluidas no binario

 final.
assim, a forma mais simples de se fazer o script de automacao e:
#!/bin/bash gcc -o executorprojeto *.c -static -lm ./executorprojeto
lembrando que o uso de *.c e obrigatorio para incluir todos os modulos desenvolvidos . adicionalmente, certi
fique-se de que o arquivo build.sh tenha permissoes de execucao (chmod +x), caso contrario o ambiente de correcao manual nao conseguira iniciar os testes.
instrucoes de entrega. o programa deve ser submetido via [run.codes]: · pagina: https://runcode

s.icmc.usp.br/ · segunda feira: codigo de matricula: ALFA9 · terca feira: codigo de matricula: BETA2
o video gravado deve ser submetido por meio de um servico de nuvem (google drive ou dropbox) e o link deve ser enviado via e-disciplinas, no qual o g

rupo vai informar o nome de cada integrante, o numero do grupo e o link de acesso . ao submeter o link, certifique-se de que as permissoes de visualizacao estao abertas para "qualquer pessoa com o link" . links que exigirem solicitacao de acesso ou q

ue apresentarem erro de 404 receberao nota zero imediatamente.
criterio de correcao criterio de avaliacao do trabalho. na correcao do trabalho, serao ponderados os seguintes aspectos.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
· corretude da execucao do programa. · atendimento as novas especificacoes do registro de cabecalho de 2
5 bytes e dos registros de dados variaveis de ate 120 bytes. · atendimento as especificacoes da sintaxe flexivel dos comandos de cada funcionalidade e do formato de saida com delimitadores pipe (|). · qualidade da documentacao doxygen entregue. a doc

umentacao interna tera um peso consideravel no trabalho. · estruturacao da solucao. o projeto deve apresentar uma organizacao adequada de arquivos e diretorios. · centralizacao do codigo. trechos de codigo que aparecem repetidamente podem ser mantido

s de forma linear para evitar a fragmentacao por excesso de funcoes. · uso de ferramentas de inteligencia artificial. o uso dessas ferramentas e permitido exclusivamente para a geracao de casos de teste e documentacao, mas proibido para a logica das

funcionalidades . o uso indevido acarretara desconto rigoroso na nota. video. integrantes que nao participarem da apresentacao receberao nota 0 no trabalho correspondente. casos de teste no [run.codes]. juntamente com a especificacao do trabalho, ser

UNIVERSIDADE DE SÃO PAULO
INSTITUTO DE CIÊNCIAS MATEMÁTICAS E DE COMPUTAÇÃO
Departamento de Ciências de Computação
Disciplina de Organização de Arquivos (SCC0215)
antos Pires · gustavo.rspires@usp.br ou telegram: @darrocaxd
Docente Profa. Dra. Cristina Dutra de Aguiar cdac@icmc.usp.br
João Gabriel Pieroli da Silva · joagabrielpieroli@usp.br ou telegram: @bielcomp24
Monitores
Pedro Lunkes Villela · pedrolunkesvillela@usp.br ou telegram: @pedrolunkes
Gustavo Ramos S
Renan Banci Catarin · renanbcata
rin@usp.br ou telegram: @Reckat
Renan Trofino Silva · renan.trofino@usp.br ou telegram: @renan823
Vinícius Souza Freitas · vininicius@usp.br ou telegram: @Vininicius
Trabalho Introdutório
ntrada e gerar um arquivo binário com esses dados, bem como realizar operações de busca, remoção e atualização. Ele é um trabalho introdutório, de forma que será usado como base para o desenvolvimento de todos os demais trabalhos da disciplina.
Este trabalho tem como objetivo obter dados de um arquivo de e
O tra

balho deve ser feito individualmente ou em trios (3 alunos) da mesma turma. A solução deve ser proposta exclusivamente pelos alunos com base nos conhecimentos adquiridos nas aulas. Consulte as notas de aula e o livro texto quando necessário.
Fundamen

tos da disciplina de Bases de Dados
A disciplina de Organização de Arquivos é uma disciplina fundamental para a disciplina de Bases de Dados. A definição dos trabalhos práticos é feita considerando esse aspecto, ou seja, os trabalhos são especificado

s em termos de várias funcionalidades, e essas funcionalidades são relacionadas tanto com desafios enfrentados no mercado de trabalho quanto com as funcionalidades da linguagem SQL (Structured Query Language), que é a linguagem utilizada por sistemas

 gerenciadores.
Av. Trabalhador São-carlense, 400 centro. São Carlos - SP cep 13566-590. Brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao de banco de dados (sgbd

s) relacionais. as caracteristicas e o detalhamento de sql serao aprendidos na disciplina de bases de dados . porem, por meio do desenvolvimento deste trabalho pratico, os alunos podem entrar em contato com alguns comandos da linguagem sql e verifica

r como eles sao implementados . os trabalhos práticos têm como objetivo armazenar e recuperar dados relacionados às estações e linhas do metrô e da cptm (companhia paulista de trens metropolitanos) da região metropolitana da cidade de são paulo (sp)

. um exemplo de uso desses dados é: "eu preciso pegar uma linha de metrô para ir para o aeroporto de guarulhos" . os dados manipulados indicam o trajeto que deve ser feito . em detalhes, os dados se referem às estações, às linhas, às distâncias entre

 as estações e aos trajetos . na disciplina de bases de dados, é ensinado que esses dados devem ser armazenados em arquivos separados, respeitando a normalização . entretanto, para aumentar a complexidade de gerencimento da redundancia nos trabalhos

da disciplina de organização de arquivos, todos os dados serão armazenados em tres arquivos distintos . isso significa que existe redundância dos dados, ou seja, o mesmo valor de dados é armazenado mais do que uma vez . descrição do arquivo de dados

. um arquivo de dados possui um registro de cabeçalho e 0 ou mais registros de dados . a descrição do registro de cabeçalho é feita conforme a definição a seguir . registro de cabeçalho. o registro de cabeçalho deve conter os seguintes campos: · stat

us: indica a consistência do arquivo de dados, devido à queda de energia, travamento do programa, etc. pode assumir os valores '1', para indicar que o arquivo de dados está inconsistente, ou '0', para indicar que o arquivo de dados está consistente .

 ao se abrir um arquivo para escrita, seu status deve ser '1' e, ao finalizar o uso desse arquivo, seu status deve ser '0' - tamanho: string de 1 byte. · topo: armazena o byte offset de um registro logicamente removido, ou 0 caso não haja registros l

ogicamente removidos - tamanho: inteiro de 4 bytes . av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias

 de computacao · proxrrn: armazena o valor do proximo rrn disponivel. deve ser iniciado com o valor '1' e deve ser alterado sempre que necessario tamanho: inteiro de 4 bytes. · nroestacoes: indica a quantidade de estacoes diferentes que estao armazen

adas no arquivo de dados . note que, se duas ou mais estacoes têm o mesmo nome, elas sao consideradas estacoes distintas - tamanho: inteiro de 4 bytes. · nroparesestacao: indica a quantidade de pares (codestacao, codproxestacao) diferentes que estao

armazenados no arquivo de dados tamanho: inteiro de 4 bytes. representacao grafica do registro de cabecalho. o tamanho do registro de cabecalho deve ser de 25 bytes, representado da seguinte forma: "0", "1", "2 3 4 5", "6 7 8 9", "10 11 12 13", "14 1

5 16 17 18 19 20 21", "22 23 24" "status", , "topo", , "proxrrn", , "nroestacoes", , "nro pares estacao" observacoes importantes. · o registro de cabecalho deve seguir estritamente a ordem definida na sua representacao grafica. · os campos sao de tam

anho variavel com delimitadores. portanto, os valores que forem armazenados devem ser finalizados por '|'. · neste projeto, o conceito de pagina de disco deve ser obrigatoriamente considerado para o calculo de offsets. registros de dados. os registro

s de dados sao de tamanho variavel, com campos de tamanho fixo e campos de tamanho variavel . para os campos de tamanho variavel, deve ser usado o metodo de delimitador de campo . os campos de tamanho fixo sao definidos da seguinte forma: · codestaca

o: codigo da estacao - inteiro - tamanho: 4 bytes. · codlinha: codigo da linha - inteiro - tamanho: 4 bytes. · codproxestacao: codigo da proxima estacao - inteiro - tamanho: 4 bytes. · distproxestacao: distancia para a proxima estacao - inteiro - tam

anho: 4 bytes. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp sao carlos scc universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao

 codlinhaintegra: codigo da linha que faz a integracao entre as linhas inteiro tamanho: 8 bytes · codestintegra: codigo da estacao que faz a integracao entre as linhas - inteiro tamanho: 8 bytes os campos de tamanho variavel sao definidos da seguinte

 forma: · nomeestacao: nome da estacao nomelinha: nome da linha adicionalmente, os seguintes campos de tamanho fixo tambem compoem cada registro. esses campos sao necessarios para o gerenciamento de registros logicamente removidos e para oferecer sup

orte para o metodo de delimitadores de campo. removido: indica se o registro esta logicamente removido. pode assumir os valores '0', para indicar que o registro esta marcado como logicamente removido, ou '1', para indicar que o registro nao esta marc

ado como removido. tamanho: string de 1 byte. proximo: armazena o byte offset do proximo registro logicamente removido tamanho: inteiro de 8 bytes. deve ser inicializado com o valor 0 quando necessario. os dados sao fornecidos juntamente com a especi

ficacao deste trabalho pratico por meio de um arquivo .json, sendo que sua especificacao esta disponivel na pagina da disciplina. no arquivo .json, o separador de campos e a chave do objeto e o primeiro registro nao especifica metadados. adicionalmen

te, campos nulos sao representados pela string "empty". representacao grafica dos registros de dados. o tamanho dos registros de dados deve ser variavel, com um limite maximo de 120 bytes, representado da seguinte forma: av. trabalhador são-carlense,

 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp 88 são carlos scc universidade de são paulo instituto de ciências matemáticas e de computação departamento de ciências de computação
representação gráfica dos registros de d
ados. o tamanho dos registros de dados deve ser variável até 120 bytes, representado da seguinte forma:
"0", "1", "9 10 11 12 13 14 15 16", "17 18 19 20", "21 22 23 24", "25 26 27 28" "removido", , "próximo (offset)", , "codestacao", , "codlinha", ,

"codproxestacao"
"29 30 31 32", "33 34 35 36 37 38 39 40", "41 42 43 44 45 46 47 48", "49...", "...119" "distproxestacao", , "codlinhaintegra", , "codestintegra", , "nomeestacao|", , "nomelinha|"
observações importantes. · cada registro de dados deve

 seguir estritamente a ordem definida na sua representação gráfica. · as strings de tamanho variável são identificadas por um delimitador pipe (|) e, portanto, devem ser finalizadas com este caractere. · os campos codestacao e nomeestacao aceitam val

ores nulos. os demais campos são de preenchimento obrigatório e não aceitam valores nulos. o arquivo .json com os dados de entrada já garante essa característica. · para os campos de tamanho fixo, os valores nulos devem ser representados pelo valor 0

. · para os campos de tamanho variável, armazenar um valor nulo significa armazenar a string "empty" seguida do delimitador. · deve ser feita a diferenciação entre o espaço utilizado e o lixo. sempre que houver lixo, ele deve ser identificado pelo ca

ractere '#'. nenhum byte do registro deve permanecer vazio, ou seja, cada byte deve armazenar um valor válido ou '#'. · não existe a necessidade de truncamento dos dados. o arquivo .json com os dados de entrada já garante essa característica. · neste

 projeto, o conceito de página de disco deve ser obrigatoriamente considerado.
programa descrição geral. implemente um programa em c por meio do qual o usuário possa obter dados de um arquivo de entrada e gerar arquivos binários com esses dados, bem

como realizar operações de busca nesses arquivos binários.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ci
encias de computacao importante. a definicao da sintaxe de cada comando bem como sua saida devem seguir com flexibilidade as especificacoes definidas em cada funcionalidade, desde que a logica de negocio seja mantida . para especificar a sintaxe de e

xecucucao, considere que o programa seja chamado de "executorprojeto" . essas orientacoes devem ser seguidas com cautela, uma vez que a avaliacao do funcionamento do programa sera realizada de forma manual pelos monitores . de forma geral, a ultima e

ntrada da entrada padrao e sempre o identificador de suas funcionalidades, conforme especificado a seguir . centralizacao. e importante manter o codigo em blocos extensos para evitar a fragmentacao excessiva do programa. trechos de programa que apare

cerem varias vezes podem ser repetidos para facilitar a leitura linear do fluxo . descricao especifica. o programa deve oferecer as seguintes funcionalidades : na linguagem sql, o comando create table e usado para criar uma tabela, a qual e implement

ada como um arquivo . geralmente, uma tabela possui um nome (que corresponde ao nome do arquivo) e varias colunas, as quais correspondem aos campos dos registros do arquivo de dados . a funcionalidade [1] representa um exemplo de implementacao do com

ando create table. [1] permita a leitura de varios registros obtidos a partir de um arquivo de entrada no formato json e a gravacao desses registros em tres arquivos de dados de saida . o arquivo de entrada no formato json e fornecido juntamente com

a especificacao do projeto, enquanto os arquivos de dados de saida devem ser gerados de acordo com as novas especificacoes deste trabalho pratico . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibiliz

ada na pagina do projeto da disciplina, para validar a integridade previa do ambiente . a funcao binarionatela deve ser usada antes que o arquivo seja aberto para escrita. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. bras

il www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [1]:
3.bin 1
arquivoentrada.json arquivosaida1.bin arquivosaida2.bin arquivosaida
onde:
arquivoentrada.json e um arquivo .json que contem os valores dos campos dos registros a serem armazenados nos arquivos binarios . arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios gerados conforme as nova

s especificacoes descritas neste trabalho pratico. 1 e o identificador da funcionalidade, agora inserido ao final da linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de saida no formato binario usando a funcao f

ornecida binarionatela antes de abrir os arquivos para escrita.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
ela antes de iniciar a funcionalidade, para validar a integridade previa do ambiente.
./executorprojeto estacao.json est1.bin est2.bin est3.bin 1
na linguagem sql, o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select. o comando mais basico consist
usar a funcao binarionat

e em especificar as clausulas select e from, da seguinte forma:
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos)
a funcionalidade [2] representa um exemplo de implementacao do

comando select . como todos os registros devem ser recuperados nessa funcionalidade, sua implementacao consiste em percorrer o arquivo de tras para frente (do ultimo registro para o primeiro).
[2] permita a recuperacao dos dados de todos os registros

 armazenados nos tres arquivos de dados de entrada, mostrando os dados de forma desorganizada e aleatoria na saida padrao para dificultar a leitura automatizada . o tratamento de 'lixo' deve ser ignorado, exibindo os caracteres '#' conforme aparecem

no disco . registros marcados como logicamente removidos (valor '0') devem ser exibidos com destaque.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias mat
ematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [2]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin 2
onde:
rios gerados conforme as especificacoes descritas neste trabalho pratico.
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos bina
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem ser mostrados de forma sequencial separados por um p

ipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos da seguinte forma: ao inves de exibir o valor 0, escreva VOID . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos da seguinte forma: EMPTY . a ordem

 de exibicao dos campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao existam registros:

arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
l 1 Parada Inglesa 2
exemplo de execucao (e mostrado um exemplo ilustrativo):
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bin 2 NULO NULO 992 2 Azul 1 Tucuruvi 1 55 4 1057 3 Azu
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
conforme visto na
 funcionalidade [2], na linguagem sql o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select . alem das clausulas select e from, outra clausula muito comum e a clausula where, que permite q

ue seja definido um criterio de busca sobre um ou mais campos, o qual e nomeado como criterio de selecao.
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos) where criterio de sel

ecao (ou seja, criterio de busca)
a funcionalidade [3] representa um exemplo de implementacao do comando select considerando a clausula where . como não existe indice definido sobre os campos dos registros, a implementacao dessa funcionalidade consis

te em percorrer o arquivo de tras para frente (da ultima pagina para a primeira).
[3] permita a recuperacao dos dados de todos os registros dos tres arquivos de dados de entrada, de forma que esses registros satisfacam qualquer um dos criterios de bu

sca (logica or) determinados pelo usuario . qualquer campo pode ser utilizado como forma de busca . adicionalmente, a busca deve ser feita considerando um ou mais campos . por exemplo, e possivel realizar a busca considerando somente o campo codestac

ao ou considerando os campos nomeestacao e nomelinha.
esta funcionalidade pode retornar 0 registros (quando nenhum satisfaz ao criterio de busca), 1 registro (quando apenas um satisfaz ao criterio de busca), ou varios registros . os valores dos campo

s do tipo string devem ser especificados entre aspas simples ('). para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . para a busca por valores nulos, d

eve-se especificar o valor void ou empty . registros marcados como logicamente removidos (status '0') devem ser exibidos obrigatoriamente . os tres arquivos de dados de entrada devem ser percorridos simultaneamente de forma decrescente.
av. trabalhad

or são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
sintaxe do comando para a funcionalidade [3]:
arquiv
osaida1.bin arquivosaida2.bin arquivosaida3.bin n 3
m1 nomecampo valorcampo1 nomecampomi valorcampoml m2 nomecampo valorcampo1 nomecampom2 valorcampom2 mn nomecampo valorcampo nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arqu
ivosaida3.bin sao os arquivos binarios de um determinado tipo, os quais foram gerados conforme as novas especificacoes descritas neste trabalho pratico . n e a quantidade de vezes que a busca deve acontecer . m e a quantidade de vezes que o par nome

do campo e valor do campo pode repetir em uma busca . o identificador da funcionalidade '3' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre nomecampo e valorcampo . os valores dos campos do tipo

 string devem ser especificados entre aspas simples (') . buscas por valores nulos devem ser especificadas com void ou empty.
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem

ser mostrados de forma sequencial separados por um pipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos como void . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos como empty . a ordem de exibicao d

os campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao seja encontrado o registro que c

ontem o valor do campo ou o campo pertence a um registro que esteja ativo (nao removido):
arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
n 1 3 1 nomeestacao 'luz' nulo nulo nulo 112 7 rubi luz 111 19 1257 56 4 amarela luz 55 55 4 nulo 10 1 azul luz 9
exemplo de execucao:
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bi
universidade de sao paulo instituto de

ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando delete e usado para remover dados em uma tabela . para tanto, devem ser especificados quais dados (ou seja, registros) devem ser removidos, de aco

rdo com algum criterio.
delete from tabela (ou seja, arquivo que contem os campos) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [4] representa um exemplo de implementacao do comando delete.
[4] permita a remocao logica de r
egistros de tres arquivos de dados de entrada, baseado na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos. a implementacao dessa funcionalidade deve ser realizada usando o conceito de fila (fifo) de registros

logicamente removidos, e deve seguir com flexibilidade a materia apresentada em sala de aula . os registros a serem removidos devem ser aqueles que satisfaçam qualquer um dos criterios de busca (logica or) determinados pelo usuario, sendo que a busca

 deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de remocao . ao se remover um registro, os valores dos bytes referentes aos campos ja armazenados no registro devem ser so

brescritos pelo caractere '#', com exceção dos valores dos campos relacionados ao tratamento da lista encadeada . a funcionalidade [4] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito,

ou seja, caso a solicitacao do usuario nao retorne nenhum registro a ser removido, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionat

ela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo inst
ituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [4]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 4
m1 nomecampo valorcampo1 m2 nomecampo valorcampo1 mn nomecam
po valorcampo nomecampomi valorcampomi nomecampom2 valorcampom2 nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho

pratico introdutorio . as remocoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de remocoes a serem realizadas . m e a quantidade de vezes que o par nome do campo e valor do campo pode repeti

r na busca pelos registros a serem removidos . o identificador da funcionalidade '4' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre o nome do campo e o valor do campo . os valores dos campos do

 tipo string devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
men
sagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 4 1 nomeestacao 'luz' 2 nomelinha 'verde'; codproxest 27
execucao da funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as remocoes.
usar a funcao binarionatela antes de iniciar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando insert into e usado para inserir dados em uma tabela . para tanto, devem ser especificados os valores a ser

em armazenados em cada coluna da tabela, de acordo com o tipo de dado definido . a funcionalidade [5] representa um exemplo de implementacao do comando insert into.
[5] permita a insercao de novos registros em tres arquivos de dados de entrada, basea

do na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e inserindo novos dados obrigatoriamente no final do arquivo, segui

ndo com flexibilidade a materia apresentada em sala de aula . o lixo que permanece no registro deve ser identificado pelo caractere '#' . na entrada da funcionalidade [5], os dados sao referentes aos seguintes campos, na ordem inversa: codestintegra,

 codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao.
campos com valores nulos, na entrada da funcionalidade, devem ser identificados com void ou empty . os valores dos campos do tipo string devem ser especi

ficados entre aspas simples (') . para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . a funcionalidade [5] deve ser executada n vezes seguidas . antes

de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são c

arlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [5]:
arquivosaida1.bin arquivosaida2.bin arq
uivosaida3.bin n 5
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao nomelinha codlinha, nomeestacao, codestacao
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao, nomelinha codlinha, nomeestacao, codestacao
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdutorio. as insercoes a serem realizadas nessa funcionalidade devem ser feitas obrig

atoriamente no final de cada um desses arquivos, desprezando qualquer espaco logicamente removido.
n e o numero de insercoes a serem realizadas. para cada insercao, deve ser informado os valores a serem inseridos nos arquivos, considerando os seguint

es campos, na ordem inversa: codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao. o identificador da funcionalidade '5' deve ser inserido ao final da primeira linha de comando.
valores nulos d

evem ser identificados, na entrada da funcionalidade, por void ou empty. cada uma das n insercoes deve ser especificada em uma linha diferente. deve ser deixado um ponto e virgula (;) entre os valores dos campos. os valores dos campos do tipo string

devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
mensagem de said
a caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 5 void; void; void; void; 'branca'; 10; 'teste'; 500 void; void; void; void; 'branca'; 10; 'nova estacao'; 501
 funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as insercoes.
usar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando update e usado para atualizar dados em uma tabela . para tanto, devem ser esp

ecificados quais valores de dados de quais campos devem ser atualizados, de acordo com algum criterio de busca dos registros a serem atualizados.
update tabela (ou seja, arquivo que contem os dados) set quais colunas e quais valores (ou seja, quais c

ampos e seus valores) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [6] representa um exemplo de implementacao do comando update.
[6] permita a atualizacao de registros de tres arquivos de dados de entrada, baseado na aborda

gem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e deve seguir com flexibilidade a materia apresentada em sala de aula . desde q

ue os registros do arquivo de dados sao de tamanho variavel (com limite de 120 bytes), se a atualizacao resultar em um registro maior que o espaco original, o registro atual deve ser marcado como removido e a nova versao deve ser inserida obrigatoria

mente no final do arquivo . o lixo que porventura permanecer no registro atualizado deve ser identificado pelo caractere '#'.
os registros a serem atualizados devem ser aqueles que satisfacam qualquer um dos criterios de busca (logica or) determinado

s pelo usuario, sendo que a busca deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de atualizacao . adicionalmente, o campo utilizado como busca nao precisa ser, necessaria

mente, o campo a ser atualizado . por exemplo, pode-se buscar pelo campo codestacao, e pode-se atualizar o campo nomelinha . campos a serem atualizados com valores nulos devem ser identificados, na entrada da funcionalidade, com void ou empty . a fun

cionalidade [6] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcio

nalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasi

l www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [6]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 6
b; valorcampob1; nomecampobmi; valorcampobm1 pl nomecampoa; valorcampoa nomecampoap1; valorcampoapi m2 nomecampob2; valorcampob2 nomecampobm2; valorcampobm2 p2 nomecampoa; valorcampoa nomecampoap2; valorcampoap2 mn nomecampobn; valorcampob nomecampob
ml nomecampo

mn; valorcampobmn pn nomecampoa; valorcampoan nomecampoapn; valorcampoapn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdu

torio . as atualizacoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de atualizacoes a serem realizadas . m e a quantidade de vezes que o par nomecampob (campo de busca) e valorcampob (valor

de busca) pode repetir para filtrar os registros, utilizando a logica or . deve ser deixado um ponto e virgula (;) entre nomecampob e valorcampob . os valores dos campos do tipo string devem ser especificados entre aspas simples (') . p e a quantidad

e de vezes que o par nomecampoa (campo a ser atualizado) e valorcampoa (novo valor) pode repetir . deve ser deixado um ponto e virgula (;) entre nomecampoa e valorcampoa . os valores das strings a serem atualizadas devem estar entre aspas simples (')

 . o identificador da funcionalidade '6' deve ser inserido ao final da primeira linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de inici

ar a execucao da funcionalidade.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
linhaintegra; 4; codestacaointegra; 55 1 codestacao; 15 1 nomeestacao; 'exemplo'
./executorprojeto est1.bin est2.bin est3.bin 2 6 2 codestacao; 1; nomeestacao; 'tucuruvi' 3 codproxestacao; 15; cod
usar a funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados f

rente as atualizacoes.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
restricoes
guintes restricoes tem que ser garantidas no desenvolvimento do trabalho:
as se
[1] o arquivo de dados deve ser gravado em disco no modo binario . o modo texto nao pode ser usado.
[2] os dados do registro descrevem os nomes dos campos, os quais nao podem s

er alterados . ademais, todos os campos devem estar presentes na implementacao, e nenhum campo adicional pode ser incluido . o tamanho e a ordem de cada campo deve obrigatoriamente seguir a nova especificacao proposta.
[3] deve haver a manipulacao de

 valores nulos, utilizando obrigatoriamente as strings "void" e "empty" e o valor numerico 0, conforme as instrucoes definidas.
[4] e necessario realizar o tratamento de truncamento de dados caso o registro atualizado exceda o limite de 120 bytes.
[5

] devem ser exibidos avisos ou mensagens de erro de acordo com a especificacao flexivel de cada funcionalidade.
[6] os dados devem ser obrigatoriamente escritos registro a registro (utilizando structs completas) . ou seja, nao e possivel escrever os

dados campo a campo . essa restricao refere-se a entrada/saida, ou seja, a forma como os dados sao escritos no arquivo.
[7] o(s) aluno(s) que desenvolveu(desenvolveram) o trabalho pratico deve(m) constar como comentario no inicio do codigo (i.e. nusp

 e nome do aluno) . para trabalhos desenvolvidos por mais do que um aluno, nao sera atribuida nota ao aluno cujos dados nao constarem no codigo fonte.
[8] todo codigo fonte deve ser documentado utilizando o padrao doxygen . a documentacao interna inc

lui a documentacao de procedimentos, de funcoes, de variaveis, de partes do codigo fonte que realizam tarefas especificas . ou seja, o codigo fonte deve ser documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais.
[9] r

estrição extra: o programa deve implementar um sistema de log que registre cada operacao de escrita realizada nos arquivos binarios em um arquivo de texto separado chamado "operacoes.log".
[10] restrição extra: o uso de memoria ram deve ser otimizado

 para que o programa nunca mantenha mais de 100 registros carregados simultaneamente, utilizando tecnicas de busca em disco (fseek).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao
paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais. [11] restrição extra: todos os ponteiros utilizados para manipulaca

o de arquivos e memoria devem ser validados imediatamente apos a declaracao, garantindo que nao haja vazamento de memoria (memory leaks) sob pena de desconsideracao da funcionalidade. [12] restrição extra: o programa deve ser capaz de lidar com inter

rupcoes de sinal (como ctrl+c), garantindo que os arquivos sejam fechados e o status de consistencia seja atualizado para '1' (inconsistente) antes da finalizacao forcada. [9] a implementacao deve ser realizada usando a linguagem de programação c . a

s funções das bibliotecas <stdio.h> devem ser utilizadas para operações relacionadas à escrita e leitura dos arquivos . a implementação não pode ser feita em qualquer outra linguagem de programação . o programa executará no [run.codes]. fundamentação

 teórica conceitos e características dos diversos métodos para representar os conceitos de campo e de registro em um arquivo de dados podem ser encontrados nos slides de sala de aula e também no livro file structures (second edition), de michael j. f

olk e bill zoellick. material para entregar arquivo compactado (a ser entregue no run.codes). deve ser preparado um arquivo.tar.gz (em vez de .zip) contendo: · código fonte do programa devidamente documentado com doxygen. · arquivo de configuracao do

 doxygen (doxyfile). vídeo (a ser entregue no e-disciplinas). um vídeo gravado pelos integrantes do grupo, o qual deve ter, no máximo, 3 minutos de gravação (em vez de 5) . o vídeo deve explicar o trabalho desenvolvido . ou seja, o grupo deve apresen

tar: cada funcionalidade e uma breve descrição de como a funcionalidade foi implementada . todos os integrantes do grupo devem participar do video, sendo que o tempo de apresentação dos integrantes deve ser balanceado . ou seja, o tempo de participaç

ão de cada integrante deve ser aproximadamente o mesmo . o uso da webcam é opcional (em vez de obrigatorio).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de cienci

as matematicas e de computacao departamento de ciencias de computacao
instrucoes para fazer o script de compilacao. no [run.codes], em vez de utilizar um makefile tradicional, voce deve fornecer um script em shell chamado "build.sh" . a diretiva prin

cipal deve garantir que a compilacao otimize o codigo para execucao em sistemas de 64 bits . adicionalmente, para utilizar a funcao binarionatela, e necessario utilizar a flag -static para garantir que todas as dependencias sejam incluidas no binario

 final.
assim, a forma mais simples de se fazer o script de automacao e:
#!/bin/bash gcc -o executorprojeto *.c -static -lm ./executorprojeto
lembrando que o uso de *.c e obrigatorio para incluir todos os modulos desenvolvidos . adicionalmente, certi
fique-se de que o arquivo build.sh tenha permissoes de execucao (chmod +x), caso contrario o ambiente de correcao manual nao conseguira iniciar os testes.
instrucoes de entrega. o programa deve ser submetido via [run.codes]: · pagina: https://runcode

s.icmc.usp.br/ · segunda feira: codigo de matricula: ALFA9 · terca feira: codigo de matricula: BETA2
o video gravado deve ser submetido por meio de um servico de nuvem (google drive ou dropbox) e o link deve ser enviado via e-disciplinas, no qual o g

rupo vai informar o nome de cada integrante, o numero do grupo e o link de acesso . ao submeter o link, certifique-se de que as permissoes de visualizacao estao abertas para "qualquer pessoa com o link" . links que exigirem solicitacao de acesso ou q

ue apresentarem erro de 404 receberao nota zero imediatamente.
criterio de correcao criterio de avaliacao do trabalho. na correcao do trabalho, serao ponderados os seguintes aspectos.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
· corretude da execucao do programa. · atendimento as novas especificacoes do registro de cabecalho de 2
5 bytes e dos registros de dados variaveis de ate 120 bytes. · atendimento as especificacoes da sintaxe flexivel dos comandos de cada funcionalidade e do formato de saida com delimitadores pipe (|). · qualidade da documentacao doxygen entregue. a doc

umentacao interna tera um peso consideravel no trabalho. · estruturacao da solucao. o projeto deve apresentar uma organizacao adequada de arquivos e diretorios. · centralizacao do codigo. trechos de codigo que aparecem repetidamente podem ser mantido

s de forma linear para evitar a fragmentacao por excesso de funcoes. · uso de ferramentas de inteligencia artificial. o uso dessas ferramentas e permitido exclusivamente para a geracao de casos de teste e documentacao, mas proibido para a logica das

funcionalidades . o uso indevido acarretara desconto rigoroso na nota. video. integrantes que nao participarem da apresentacao receberao nota 0 no trabalho correspondente. casos de teste no [run.codes]. juntamente com a especificacao do trabalho, ser

UNIVERSIDADE DE SÃO PAULO
INSTITUTO DE CIÊNCIAS MATEMÁTICAS E DE COMPUTAÇÃO
Departamento de Ciências de Computação
Disciplina de Organização de Arquivos (SCC0215)
antos Pires · gustavo.rspires@usp.br ou telegram: @darrocaxd
Docente Profa. Dra. Cristina Dutra de Aguiar cdac@icmc.usp.br
João Gabriel Pieroli da Silva · joagabrielpieroli@usp.br ou telegram: @bielcomp24
Monitores
Pedro Lunkes Villela · pedrolunkesvillela@usp.br ou telegram: @pedrolunkes
Gustavo Ramos S
Renan Banci Catarin · renanbcata
rin@usp.br ou telegram: @Reckat
Renan Trofino Silva · renan.trofino@usp.br ou telegram: @renan823
Vinícius Souza Freitas · vininicius@usp.br ou telegram: @Vininicius
Trabalho Introdutório
ntrada e gerar um arquivo binário com esses dados, bem como realizar operações de busca, remoção e atualização. Ele é um trabalho introdutório, de forma que será usado como base para o desenvolvimento de todos os demais trabalhos da disciplina.
Este trabalho tem como objetivo obter dados de um arquivo de e
O tra

balho deve ser feito individualmente ou em trios (3 alunos) da mesma turma. A solução deve ser proposta exclusivamente pelos alunos com base nos conhecimentos adquiridos nas aulas. Consulte as notas de aula e o livro texto quando necessário.
Fundamen

tos da disciplina de Bases de Dados
A disciplina de Organização de Arquivos é uma disciplina fundamental para a disciplina de Bases de Dados. A definição dos trabalhos práticos é feita considerando esse aspecto, ou seja, os trabalhos são especificado

s em termos de várias funcionalidades, e essas funcionalidades são relacionadas tanto com desafios enfrentados no mercado de trabalho quanto com as funcionalidades da linguagem SQL (Structured Query Language), que é a linguagem utilizada por sistemas

 gerenciadores.
Av. Trabalhador São-carlense, 400 centro. São Carlos - SP cep 13566-590. Brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao de banco de dados (sgbd

s) relacionais. as caracteristicas e o detalhamento de sql serao aprendidos na disciplina de bases de dados . porem, por meio do desenvolvimento deste trabalho pratico, os alunos podem entrar em contato com alguns comandos da linguagem sql e verifica

r como eles sao implementados . os trabalhos práticos têm como objetivo armazenar e recuperar dados relacionados às estações e linhas do metrô e da cptm (companhia paulista de trens metropolitanos) da região metropolitana da cidade de são paulo (sp)

. um exemplo de uso desses dados é: "eu preciso pegar uma linha de metrô para ir para o aeroporto de guarulhos" . os dados manipulados indicam o trajeto que deve ser feito . em detalhes, os dados se referem às estações, às linhas, às distâncias entre

 as estações e aos trajetos . na disciplina de bases de dados, é ensinado que esses dados devem ser armazenados em arquivos separados, respeitando a normalização . entretanto, para aumentar a complexidade de gerencimento da redundancia nos trabalhos

da disciplina de organização de arquivos, todos os dados serão armazenados em tres arquivos distintos . isso significa que existe redundância dos dados, ou seja, o mesmo valor de dados é armazenado mais do que uma vez . descrição do arquivo de dados

. um arquivo de dados possui um registro de cabeçalho e 0 ou mais registros de dados . a descrição do registro de cabeçalho é feita conforme a definição a seguir . registro de cabeçalho. o registro de cabeçalho deve conter os seguintes campos: · stat

us: indica a consistência do arquivo de dados, devido à queda de energia, travamento do programa, etc. pode assumir os valores '1', para indicar que o arquivo de dados está inconsistente, ou '0', para indicar que o arquivo de dados está consistente .

 ao se abrir um arquivo para escrita, seu status deve ser '1' e, ao finalizar o uso desse arquivo, seu status deve ser '0' - tamanho: string de 1 byte. · topo: armazena o byte offset de um registro logicamente removido, ou 0 caso não haja registros l

ogicamente removidos - tamanho: inteiro de 4 bytes . av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias

 de computacao · proxrrn: armazena o valor do proximo rrn disponivel. deve ser iniciado com o valor '1' e deve ser alterado sempre que necessario tamanho: inteiro de 4 bytes. · nroestacoes: indica a quantidade de estacoes diferentes que estao armazen

adas no arquivo de dados . note que, se duas ou mais estacoes têm o mesmo nome, elas sao consideradas estacoes distintas - tamanho: inteiro de 4 bytes. · nroparesestacao: indica a quantidade de pares (codestacao, codproxestacao) diferentes que estao

armazenados no arquivo de dados tamanho: inteiro de 4 bytes. representacao grafica do registro de cabecalho. o tamanho do registro de cabecalho deve ser de 25 bytes, representado da seguinte forma: "0", "1", "2 3 4 5", "6 7 8 9", "10 11 12 13", "14 1

5 16 17 18 19 20 21", "22 23 24" "status", , "topo", , "proxrrn", , "nroestacoes", , "nro pares estacao" observacoes importantes. · o registro de cabecalho deve seguir estritamente a ordem definida na sua representacao grafica. · os campos sao de tam

anho variavel com delimitadores. portanto, os valores que forem armazenados devem ser finalizados por '|'. · neste projeto, o conceito de pagina de disco deve ser obrigatoriamente considerado para o calculo de offsets. registros de dados. os registro

s de dados sao de tamanho variavel, com campos de tamanho fixo e campos de tamanho variavel . para os campos de tamanho variavel, deve ser usado o metodo de delimitador de campo . os campos de tamanho fixo sao definidos da seguinte forma: · codestaca

o: codigo da estacao - inteiro - tamanho: 4 bytes. · codlinha: codigo da linha - inteiro - tamanho: 4 bytes. · codproxestacao: codigo da proxima estacao - inteiro - tamanho: 4 bytes. · distproxestacao: distancia para a proxima estacao - inteiro - tam

anho: 4 bytes. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp sao carlos scc universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao

 codlinhaintegra: codigo da linha que faz a integracao entre as linhas inteiro tamanho: 8 bytes · codestintegra: codigo da estacao que faz a integracao entre as linhas - inteiro tamanho: 8 bytes os campos de tamanho variavel sao definidos da seguinte

 forma: · nomeestacao: nome da estacao nomelinha: nome da linha adicionalmente, os seguintes campos de tamanho fixo tambem compoem cada registro. esses campos sao necessarios para o gerenciamento de registros logicamente removidos e para oferecer sup

orte para o metodo de delimitadores de campo. removido: indica se o registro esta logicamente removido. pode assumir os valores '0', para indicar que o registro esta marcado como logicamente removido, ou '1', para indicar que o registro nao esta marc

ado como removido. tamanho: string de 1 byte. proximo: armazena o byte offset do proximo registro logicamente removido tamanho: inteiro de 8 bytes. deve ser inicializado com o valor 0 quando necessario. os dados sao fornecidos juntamente com a especi

ficacao deste trabalho pratico por meio de um arquivo .json, sendo que sua especificacao esta disponivel na pagina da disciplina. no arquivo .json, o separador de campos e a chave do objeto e o primeiro registro nao especifica metadados. adicionalmen

te, campos nulos sao representados pela string "empty". representacao grafica dos registros de dados. o tamanho dos registros de dados deve ser variavel, com um limite maximo de 120 bytes, representado da seguinte forma: av. trabalhador são-carlense,

 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp 88 são carlos scc universidade de são paulo instituto de ciências matemáticas e de computação departamento de ciências de computação
representação gráfica dos registros de d
ados. o tamanho dos registros de dados deve ser variável até 120 bytes, representado da seguinte forma:
"0", "1", "9 10 11 12 13 14 15 16", "17 18 19 20", "21 22 23 24", "25 26 27 28" "removido", , "próximo (offset)", , "codestacao", , "codlinha", ,

"codproxestacao"
"29 30 31 32", "33 34 35 36 37 38 39 40", "41 42 43 44 45 46 47 48", "49...", "...119" "distproxestacao", , "codlinhaintegra", , "codestintegra", , "nomeestacao|", , "nomelinha|"
observações importantes. · cada registro de dados deve

 seguir estritamente a ordem definida na sua representação gráfica. · as strings de tamanho variável são identificadas por um delimitador pipe (|) e, portanto, devem ser finalizadas com este caractere. · os campos codestacao e nomeestacao aceitam val

ores nulos. os demais campos são de preenchimento obrigatório e não aceitam valores nulos. o arquivo .json com os dados de entrada já garante essa característica. · para os campos de tamanho fixo, os valores nulos devem ser representados pelo valor 0

. · para os campos de tamanho variável, armazenar um valor nulo significa armazenar a string "empty" seguida do delimitador. · deve ser feita a diferenciação entre o espaço utilizado e o lixo. sempre que houver lixo, ele deve ser identificado pelo ca

ractere '#'. nenhum byte do registro deve permanecer vazio, ou seja, cada byte deve armazenar um valor válido ou '#'. · não existe a necessidade de truncamento dos dados. o arquivo .json com os dados de entrada já garante essa característica. · neste

 projeto, o conceito de página de disco deve ser obrigatoriamente considerado.
programa descrição geral. implemente um programa em c por meio do qual o usuário possa obter dados de um arquivo de entrada e gerar arquivos binários com esses dados, bem

como realizar operações de busca nesses arquivos binários.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ci
encias de computacao importante. a definicao da sintaxe de cada comando bem como sua saida devem seguir com flexibilidade as especificacoes definidas em cada funcionalidade, desde que a logica de negocio seja mantida . para especificar a sintaxe de e

xecucucao, considere que o programa seja chamado de "executorprojeto" . essas orientacoes devem ser seguidas com cautela, uma vez que a avaliacao do funcionamento do programa sera realizada de forma manual pelos monitores . de forma geral, a ultima e

ntrada da entrada padrao e sempre o identificador de suas funcionalidades, conforme especificado a seguir . centralizacao. e importante manter o codigo em blocos extensos para evitar a fragmentacao excessiva do programa. trechos de programa que apare

cerem varias vezes podem ser repetidos para facilitar a leitura linear do fluxo . descricao especifica. o programa deve oferecer as seguintes funcionalidades : na linguagem sql, o comando create table e usado para criar uma tabela, a qual e implement

ada como um arquivo . geralmente, uma tabela possui um nome (que corresponde ao nome do arquivo) e varias colunas, as quais correspondem aos campos dos registros do arquivo de dados . a funcionalidade [1] representa um exemplo de implementacao do com

ando create table. [1] permita a leitura de varios registros obtidos a partir de um arquivo de entrada no formato json e a gravacao desses registros em tres arquivos de dados de saida . o arquivo de entrada no formato json e fornecido juntamente com

a especificacao do projeto, enquanto os arquivos de dados de saida devem ser gerados de acordo com as novas especificacoes deste trabalho pratico . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibiliz

ada na pagina do projeto da disciplina, para validar a integridade previa do ambiente . a funcao binarionatela deve ser usada antes que o arquivo seja aberto para escrita. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. bras

il www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [1]:
3.bin 1
arquivoentrada.json arquivosaida1.bin arquivosaida2.bin arquivosaida
onde:
arquivoentrada.json e um arquivo .json que contem os valores dos campos dos registros a serem armazenados nos arquivos binarios . arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios gerados conforme as nova

s especificacoes descritas neste trabalho pratico. 1 e o identificador da funcionalidade, agora inserido ao final da linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de saida no formato binario usando a funcao f

ornecida binarionatela antes de abrir os arquivos para escrita.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
ela antes de iniciar a funcionalidade, para validar a integridade previa do ambiente.
./executorprojeto estacao.json est1.bin est2.bin est3.bin 1
na linguagem sql, o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select. o comando mais basico consist
usar a funcao binarionat

e em especificar as clausulas select e from, da seguinte forma:
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos)
a funcionalidade [2] representa um exemplo de implementacao do

comando select . como todos os registros devem ser recuperados nessa funcionalidade, sua implementacao consiste em percorrer o arquivo de tras para frente (do ultimo registro para o primeiro).
[2] permita a recuperacao dos dados de todos os registros

 armazenados nos tres arquivos de dados de entrada, mostrando os dados de forma desorganizada e aleatoria na saida padrao para dificultar a leitura automatizada . o tratamento de 'lixo' deve ser ignorado, exibindo os caracteres '#' conforme aparecem

no disco . registros marcados como logicamente removidos (valor '0') devem ser exibidos com destaque.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias mat
ematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [2]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin 2
onde:
rios gerados conforme as especificacoes descritas neste trabalho pratico.
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos bina
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem ser mostrados de forma sequencial separados por um p

ipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos da seguinte forma: ao inves de exibir o valor 0, escreva VOID . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos da seguinte forma: EMPTY . a ordem

 de exibicao dos campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao existam registros:

arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
l 1 Parada Inglesa 2
exemplo de execucao (e mostrado um exemplo ilustrativo):
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bin 2 NULO NULO 992 2 Azul 1 Tucuruvi 1 55 4 1057 3 Azu
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
conforme visto na
 funcionalidade [2], na linguagem sql o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select . alem das clausulas select e from, outra clausula muito comum e a clausula where, que permite q

ue seja definido um criterio de busca sobre um ou mais campos, o qual e nomeado como criterio de selecao.
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos) where criterio de sel

ecao (ou seja, criterio de busca)
a funcionalidade [3] representa um exemplo de implementacao do comando select considerando a clausula where . como não existe indice definido sobre os campos dos registros, a implementacao dessa funcionalidade consis

te em percorrer o arquivo de tras para frente (da ultima pagina para a primeira).
[3] permita a recuperacao dos dados de todos os registros dos tres arquivos de dados de entrada, de forma que esses registros satisfacam qualquer um dos criterios de bu

sca (logica or) determinados pelo usuario . qualquer campo pode ser utilizado como forma de busca . adicionalmente, a busca deve ser feita considerando um ou mais campos . por exemplo, e possivel realizar a busca considerando somente o campo codestac

ao ou considerando os campos nomeestacao e nomelinha.
esta funcionalidade pode retornar 0 registros (quando nenhum satisfaz ao criterio de busca), 1 registro (quando apenas um satisfaz ao criterio de busca), ou varios registros . os valores dos campo

s do tipo string devem ser especificados entre aspas simples ('). para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . para a busca por valores nulos, d

eve-se especificar o valor void ou empty . registros marcados como logicamente removidos (status '0') devem ser exibidos obrigatoriamente . os tres arquivos de dados de entrada devem ser percorridos simultaneamente de forma decrescente.
av. trabalhad

or são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
sintaxe do comando para a funcionalidade [3]:
arquiv
osaida1.bin arquivosaida2.bin arquivosaida3.bin n 3
m1 nomecampo valorcampo1 nomecampomi valorcampoml m2 nomecampo valorcampo1 nomecampom2 valorcampom2 mn nomecampo valorcampo nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arqu
ivosaida3.bin sao os arquivos binarios de um determinado tipo, os quais foram gerados conforme as novas especificacoes descritas neste trabalho pratico . n e a quantidade de vezes que a busca deve acontecer . m e a quantidade de vezes que o par nome

do campo e valor do campo pode repetir em uma busca . o identificador da funcionalidade '3' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre nomecampo e valorcampo . os valores dos campos do tipo

 string devem ser especificados entre aspas simples (') . buscas por valores nulos devem ser especificadas com void ou empty.
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem

ser mostrados de forma sequencial separados por um pipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos como void . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos como empty . a ordem de exibicao d

os campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao seja encontrado o registro que c

ontem o valor do campo ou o campo pertence a um registro que esteja ativo (nao removido):
arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
n 1 3 1 nomeestacao 'luz' nulo nulo nulo 112 7 rubi luz 111 19 1257 56 4 amarela luz 55 55 4 nulo 10 1 azul luz 9
exemplo de execucao:
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bi
universidade de sao paulo instituto de

ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando delete e usado para remover dados em uma tabela . para tanto, devem ser especificados quais dados (ou seja, registros) devem ser removidos, de aco

rdo com algum criterio.
delete from tabela (ou seja, arquivo que contem os campos) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [4] representa um exemplo de implementacao do comando delete.
[4] permita a remocao logica de r
egistros de tres arquivos de dados de entrada, baseado na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos. a implementacao dessa funcionalidade deve ser realizada usando o conceito de fila (fifo) de registros

logicamente removidos, e deve seguir com flexibilidade a materia apresentada em sala de aula . os registros a serem removidos devem ser aqueles que satisfaçam qualquer um dos criterios de busca (logica or) determinados pelo usuario, sendo que a busca

 deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de remocao . ao se remover um registro, os valores dos bytes referentes aos campos ja armazenados no registro devem ser so

brescritos pelo caractere '#', com exceção dos valores dos campos relacionados ao tratamento da lista encadeada . a funcionalidade [4] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito,

ou seja, caso a solicitacao do usuario nao retorne nenhum registro a ser removido, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionat

ela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo inst
ituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [4]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 4
m1 nomecampo valorcampo1 m2 nomecampo valorcampo1 mn nomecam
po valorcampo nomecampomi valorcampomi nomecampom2 valorcampom2 nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho

pratico introdutorio . as remocoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de remocoes a serem realizadas . m e a quantidade de vezes que o par nome do campo e valor do campo pode repeti

r na busca pelos registros a serem removidos . o identificador da funcionalidade '4' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre o nome do campo e o valor do campo . os valores dos campos do

 tipo string devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
men
sagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 4 1 nomeestacao 'luz' 2 nomelinha 'verde'; codproxest 27
execucao da funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as remocoes.
usar a funcao binarionatela antes de iniciar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando insert into e usado para inserir dados em uma tabela . para tanto, devem ser especificados os valores a ser

em armazenados em cada coluna da tabela, de acordo com o tipo de dado definido . a funcionalidade [5] representa um exemplo de implementacao do comando insert into.
[5] permita a insercao de novos registros em tres arquivos de dados de entrada, basea

do na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e inserindo novos dados obrigatoriamente no final do arquivo, segui

ndo com flexibilidade a materia apresentada em sala de aula . o lixo que permanece no registro deve ser identificado pelo caractere '#' . na entrada da funcionalidade [5], os dados sao referentes aos seguintes campos, na ordem inversa: codestintegra,

 codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao.
campos com valores nulos, na entrada da funcionalidade, devem ser identificados com void ou empty . os valores dos campos do tipo string devem ser especi

ficados entre aspas simples (') . para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . a funcionalidade [5] deve ser executada n vezes seguidas . antes

de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são c

arlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [5]:
arquivosaida1.bin arquivosaida2.bin arq
uivosaida3.bin n 5
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao nomelinha codlinha, nomeestacao, codestacao
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao, nomelinha codlinha, nomeestacao, codestacao
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdutorio. as insercoes a serem realizadas nessa funcionalidade devem ser feitas obrig

atoriamente no final de cada um desses arquivos, desprezando qualquer espaco logicamente removido.
n e o numero de insercoes a serem realizadas. para cada insercao, deve ser informado os valores a serem inseridos nos arquivos, considerando os seguint

es campos, na ordem inversa: codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao. o identificador da funcionalidade '5' deve ser inserido ao final da primeira linha de comando.
valores nulos d

evem ser identificados, na entrada da funcionalidade, por void ou empty. cada uma das n insercoes deve ser especificada em uma linha diferente. deve ser deixado um ponto e virgula (;) entre os valores dos campos. os valores dos campos do tipo string

devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
mensagem de said
a caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 5 void; void; void; void; 'branca'; 10; 'teste'; 500 void; void; void; void; 'branca'; 10; 'nova estacao'; 501
 funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as insercoes.
usar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando update e usado para atualizar dados em uma tabela . para tanto, devem ser esp

ecificados quais valores de dados de quais campos devem ser atualizados, de acordo com algum criterio de busca dos registros a serem atualizados.
update tabela (ou seja, arquivo que contem os dados) set quais colunas e quais valores (ou seja, quais c

ampos e seus valores) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [6] representa um exemplo de implementacao do comando update.
[6] permita a atualizacao de registros de tres arquivos de dados de entrada, baseado na aborda

gem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e deve seguir com flexibilidade a materia apresentada em sala de aula . desde q

ue os registros do arquivo de dados sao de tamanho variavel (com limite de 120 bytes), se a atualizacao resultar em um registro maior que o espaco original, o registro atual deve ser marcado como removido e a nova versao deve ser inserida obrigatoria

mente no final do arquivo . o lixo que porventura permanecer no registro atualizado deve ser identificado pelo caractere '#'.
os registros a serem atualizados devem ser aqueles que satisfacam qualquer um dos criterios de busca (logica or) determinado

s pelo usuario, sendo que a busca deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de atualizacao . adicionalmente, o campo utilizado como busca nao precisa ser, necessaria

mente, o campo a ser atualizado . por exemplo, pode-se buscar pelo campo codestacao, e pode-se atualizar o campo nomelinha . campos a serem atualizados com valores nulos devem ser identificados, na entrada da funcionalidade, com void ou empty . a fun

cionalidade [6] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcio

nalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasi

l www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [6]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 6
b; valorcampob1; nomecampobmi; valorcampobm1 pl nomecampoa; valorcampoa nomecampoap1; valorcampoapi m2 nomecampob2; valorcampob2 nomecampobm2; valorcampobm2 p2 nomecampoa; valorcampoa nomecampoap2; valorcampoap2 mn nomecampobn; valorcampob nomecampob
ml nomecampo

mn; valorcampobmn pn nomecampoa; valorcampoan nomecampoapn; valorcampoapn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdu

torio . as atualizacoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de atualizacoes a serem realizadas . m e a quantidade de vezes que o par nomecampob (campo de busca) e valorcampob (valor

de busca) pode repetir para filtrar os registros, utilizando a logica or . deve ser deixado um ponto e virgula (;) entre nomecampob e valorcampob . os valores dos campos do tipo string devem ser especificados entre aspas simples (') . p e a quantidad

e de vezes que o par nomecampoa (campo a ser atualizado) e valorcampoa (novo valor) pode repetir . deve ser deixado um ponto e virgula (;) entre nomecampoa e valorcampoa . os valores das strings a serem atualizadas devem estar entre aspas simples (')

 . o identificador da funcionalidade '6' deve ser inserido ao final da primeira linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de inici

ar a execucao da funcionalidade.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
linhaintegra; 4; codestacaointegra; 55 1 codestacao; 15 1 nomeestacao; 'exemplo'
./executorprojeto est1.bin est2.bin est3.bin 2 6 2 codestacao; 1; nomeestacao; 'tucuruvi' 3 codproxestacao; 15; cod
usar a funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados f

rente as atualizacoes.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
restricoes
guintes restricoes tem que ser garantidas no desenvolvimento do trabalho:
as se
[1] o arquivo de dados deve ser gravado em disco no modo binario . o modo texto nao pode ser usado.
[2] os dados do registro descrevem os nomes dos campos, os quais nao podem s

er alterados . ademais, todos os campos devem estar presentes na implementacao, e nenhum campo adicional pode ser incluido . o tamanho e a ordem de cada campo deve obrigatoriamente seguir a nova especificacao proposta.
[3] deve haver a manipulacao de

 valores nulos, utilizando obrigatoriamente as strings "void" e "empty" e o valor numerico 0, conforme as instrucoes definidas.
[4] e necessario realizar o tratamento de truncamento de dados caso o registro atualizado exceda o limite de 120 bytes.
[5

] devem ser exibidos avisos ou mensagens de erro de acordo com a especificacao flexivel de cada funcionalidade.
[6] os dados devem ser obrigatoriamente escritos registro a registro (utilizando structs completas) . ou seja, nao e possivel escrever os

dados campo a campo . essa restricao refere-se a entrada/saida, ou seja, a forma como os dados sao escritos no arquivo.
[7] o(s) aluno(s) que desenvolveu(desenvolveram) o trabalho pratico deve(m) constar como comentario no inicio do codigo (i.e. nusp

 e nome do aluno) . para trabalhos desenvolvidos por mais do que um aluno, nao sera atribuida nota ao aluno cujos dados nao constarem no codigo fonte.
[8] todo codigo fonte deve ser documentado utilizando o padrao doxygen . a documentacao interna inc

lui a documentacao de procedimentos, de funcoes, de variaveis, de partes do codigo fonte que realizam tarefas especificas . ou seja, o codigo fonte deve ser documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais.
[9] r

estrição extra: o programa deve implementar um sistema de log que registre cada operacao de escrita realizada nos arquivos binarios em um arquivo de texto separado chamado "operacoes.log".
[10] restrição extra: o uso de memoria ram deve ser otimizado

 para que o programa nunca mantenha mais de 100 registros carregados simultaneamente, utilizando tecnicas de busca em disco (fseek).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao
paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais. [11] restrição extra: todos os ponteiros utilizados para manipulaca

o de arquivos e memoria devem ser validados imediatamente apos a declaracao, garantindo que nao haja vazamento de memoria (memory leaks) sob pena de desconsideracao da funcionalidade. [12] restrição extra: o programa deve ser capaz de lidar com inter

rupcoes de sinal (como ctrl+c), garantindo que os arquivos sejam fechados e o status de consistencia seja atualizado para '1' (inconsistente) antes da finalizacao forcada. [9] a implementacao deve ser realizada usando a linguagem de programação c . a

s funções das bibliotecas <stdio.h> devem ser utilizadas para operações relacionadas à escrita e leitura dos arquivos . a implementação não pode ser feita em qualquer outra linguagem de programação . o programa executará no [run.codes]. fundamentação

 teórica conceitos e características dos diversos métodos para representar os conceitos de campo e de registro em um arquivo de dados podem ser encontrados nos slides de sala de aula e também no livro file structures (second edition), de michael j. f

olk e bill zoellick. material para entregar arquivo compactado (a ser entregue no run.codes). deve ser preparado um arquivo.tar.gz (em vez de .zip) contendo: · código fonte do programa devidamente documentado com doxygen. · arquivo de configuracao do

 doxygen (doxyfile). vídeo (a ser entregue no e-disciplinas). um vídeo gravado pelos integrantes do grupo, o qual deve ter, no máximo, 3 minutos de gravação (em vez de 5) . o vídeo deve explicar o trabalho desenvolvido . ou seja, o grupo deve apresen

tar: cada funcionalidade e uma breve descrição de como a funcionalidade foi implementada . todos os integrantes do grupo devem participar do video, sendo que o tempo de apresentação dos integrantes deve ser balanceado . ou seja, o tempo de participaç

ão de cada integrante deve ser aproximadamente o mesmo . o uso da webcam é opcional (em vez de obrigatorio).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de cienci

as matematicas e de computacao departamento de ciencias de computacao
instrucoes para fazer o script de compilacao. no [run.codes], em vez de utilizar um makefile tradicional, voce deve fornecer um script em shell chamado "build.sh" . a diretiva prin

cipal deve garantir que a compilacao otimize o codigo para execucao em sistemas de 64 bits . adicionalmente, para utilizar a funcao binarionatela, e necessario utilizar a flag -static para garantir que todas as dependencias sejam incluidas no binario

 final.
assim, a forma mais simples de se fazer o script de automacao e:
#!/bin/bash gcc -o executorprojeto *.c -static -lm ./executorprojeto
lembrando que o uso de *.c e obrigatorio para incluir todos os modulos desenvolvidos . adicionalmente, certi
fique-se de que o arquivo build.sh tenha permissoes de execucao (chmod +x), caso contrario o ambiente de correcao manual nao conseguira iniciar os testes.
instrucoes de entrega. o programa deve ser submetido via [run.codes]: · pagina: https://runcode

s.icmc.usp.br/ · segunda feira: codigo de matricula: ALFA9 · terca feira: codigo de matricula: BETA2
o video gravado deve ser submetido por meio de um servico de nuvem (google drive ou dropbox) e o link deve ser enviado via e-disciplinas, no qual o g

rupo vai informar o nome de cada integrante, o numero do grupo e o link de acesso . ao submeter o link, certifique-se de que as permissoes de visualizacao estao abertas para "qualquer pessoa com o link" . links que exigirem solicitacao de acesso ou q

ue apresentarem erro de 404 receberao nota zero imediatamente.
criterio de correcao criterio de avaliacao do trabalho. na correcao do trabalho, serao ponderados os seguintes aspectos.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
· corretude da execucao do programa. · atendimento as novas especificacoes do registro de cabecalho de 2
5 bytes e dos registros de dados variaveis de ate 120 bytes. · atendimento as especificacoes da sintaxe flexivel dos comandos de cada funcionalidade e do formato de saida com delimitadores pipe (|). · qualidade da documentacao doxygen entregue. a doc

umentacao interna tera um peso consideravel no trabalho. · estruturacao da solucao. o projeto deve apresentar uma organizacao adequada de arquivos e diretorios. · centralizacao do codigo. trechos de codigo que aparecem repetidamente podem ser mantido

s de forma linear para evitar a fragmentacao por excesso de funcoes. · uso de ferramentas de inteligencia artificial. o uso dessas ferramentas e permitido exclusivamente para a geracao de casos de teste e documentacao, mas proibido para a logica das

funcionalidades . o uso indevido acarretara desconto rigoroso na nota. video. integrantes que nao participarem da apresentacao receberao nota 0 no trabalho correspondente. casos de teste no [run.codes]. juntamente com a especificacao do trabalho, ser

UNIVERSIDADE DE SÃO PAULO
INSTITUTO DE CIÊNCIAS MATEMÁTICAS E DE COMPUTAÇÃO
Departamento de Ciências de Computação
Disciplina de Organização de Arquivos (SCC0215)
antos Pires · gustavo.rspires@usp.br ou telegram: @darrocaxd
Docente Profa. Dra. Cristina Dutra de Aguiar cdac@icmc.usp.br
João Gabriel Pieroli da Silva · joagabrielpieroli@usp.br ou telegram: @bielcomp24
Monitores
Pedro Lunkes Villela · pedrolunkesvillela@usp.br ou telegram: @pedrolunkes
Gustavo Ramos S
Renan Banci Catarin · renanbcata
rin@usp.br ou telegram: @Reckat
Renan Trofino Silva · renan.trofino@usp.br ou telegram: @renan823
Vinícius Souza Freitas · vininicius@usp.br ou telegram: @Vininicius
Trabalho Introdutório
ntrada e gerar um arquivo binário com esses dados, bem como realizar operações de busca, remoção e atualização. Ele é um trabalho introdutório, de forma que será usado como base para o desenvolvimento de todos os demais trabalhos da disciplina.
Este trabalho tem como objetivo obter dados de um arquivo de e
O tra

balho deve ser feito individualmente ou em trios (3 alunos) da mesma turma. A solução deve ser proposta exclusivamente pelos alunos com base nos conhecimentos adquiridos nas aulas. Consulte as notas de aula e o livro texto quando necessário.
Fundamen

tos da disciplina de Bases de Dados
A disciplina de Organização de Arquivos é uma disciplina fundamental para a disciplina de Bases de Dados. A definição dos trabalhos práticos é feita considerando esse aspecto, ou seja, os trabalhos são especificado

s em termos de várias funcionalidades, e essas funcionalidades são relacionadas tanto com desafios enfrentados no mercado de trabalho quanto com as funcionalidades da linguagem SQL (Structured Query Language), que é a linguagem utilizada por sistemas

 gerenciadores.
Av. Trabalhador São-carlense, 400 centro. São Carlos - SP cep 13566-590. Brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao de banco de dados (sgbd

s) relacionais. as caracteristicas e o detalhamento de sql serao aprendidos na disciplina de bases de dados . porem, por meio do desenvolvimento deste trabalho pratico, os alunos podem entrar em contato com alguns comandos da linguagem sql e verifica

r como eles sao implementados . os trabalhos práticos têm como objetivo armazenar e recuperar dados relacionados às estações e linhas do metrô e da cptm (companhia paulista de trens metropolitanos) da região metropolitana da cidade de são paulo (sp)

. um exemplo de uso desses dados é: "eu preciso pegar uma linha de metrô para ir para o aeroporto de guarulhos" . os dados manipulados indicam o trajeto que deve ser feito . em detalhes, os dados se referem às estações, às linhas, às distâncias entre

 as estações e aos trajetos . na disciplina de bases de dados, é ensinado que esses dados devem ser armazenados em arquivos separados, respeitando a normalização . entretanto, para aumentar a complexidade de gerencimento da redundancia nos trabalhos

da disciplina de organização de arquivos, todos os dados serão armazenados em tres arquivos distintos . isso significa que existe redundância dos dados, ou seja, o mesmo valor de dados é armazenado mais do que uma vez . descrição do arquivo de dados

. um arquivo de dados possui um registro de cabeçalho e 0 ou mais registros de dados . a descrição do registro de cabeçalho é feita conforme a definição a seguir . registro de cabeçalho. o registro de cabeçalho deve conter os seguintes campos: · stat

us: indica a consistência do arquivo de dados, devido à queda de energia, travamento do programa, etc. pode assumir os valores '1', para indicar que o arquivo de dados está inconsistente, ou '0', para indicar que o arquivo de dados está consistente .

 ao se abrir um arquivo para escrita, seu status deve ser '1' e, ao finalizar o uso desse arquivo, seu status deve ser '0' - tamanho: string de 1 byte. · topo: armazena o byte offset de um registro logicamente removido, ou 0 caso não haja registros l

ogicamente removidos - tamanho: inteiro de 4 bytes . av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias

 de computacao · proxrrn: armazena o valor do proximo rrn disponivel. deve ser iniciado com o valor '1' e deve ser alterado sempre que necessario tamanho: inteiro de 4 bytes. · nroestacoes: indica a quantidade de estacoes diferentes que estao armazen

adas no arquivo de dados . note que, se duas ou mais estacoes têm o mesmo nome, elas sao consideradas estacoes distintas - tamanho: inteiro de 4 bytes. · nroparesestacao: indica a quantidade de pares (codestacao, codproxestacao) diferentes que estao

armazenados no arquivo de dados tamanho: inteiro de 4 bytes. representacao grafica do registro de cabecalho. o tamanho do registro de cabecalho deve ser de 25 bytes, representado da seguinte forma: "0", "1", "2 3 4 5", "6 7 8 9", "10 11 12 13", "14 1

5 16 17 18 19 20 21", "22 23 24" "status", , "topo", , "proxrrn", , "nroestacoes", , "nro pares estacao" observacoes importantes. · o registro de cabecalho deve seguir estritamente a ordem definida na sua representacao grafica. · os campos sao de tam

anho variavel com delimitadores. portanto, os valores que forem armazenados devem ser finalizados por '|'. · neste projeto, o conceito de pagina de disco deve ser obrigatoriamente considerado para o calculo de offsets. registros de dados. os registro

s de dados sao de tamanho variavel, com campos de tamanho fixo e campos de tamanho variavel . para os campos de tamanho variavel, deve ser usado o metodo de delimitador de campo . os campos de tamanho fixo sao definidos da seguinte forma: · codestaca

o: codigo da estacao - inteiro - tamanho: 4 bytes. · codlinha: codigo da linha - inteiro - tamanho: 4 bytes. · codproxestacao: codigo da proxima estacao - inteiro - tamanho: 4 bytes. · distproxestacao: distancia para a proxima estacao - inteiro - tam

anho: 4 bytes. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp sao carlos scc universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao

 codlinhaintegra: codigo da linha que faz a integracao entre as linhas inteiro tamanho: 8 bytes · codestintegra: codigo da estacao que faz a integracao entre as linhas - inteiro tamanho: 8 bytes os campos de tamanho variavel sao definidos da seguinte

 forma: · nomeestacao: nome da estacao nomelinha: nome da linha adicionalmente, os seguintes campos de tamanho fixo tambem compoem cada registro. esses campos sao necessarios para o gerenciamento de registros logicamente removidos e para oferecer sup

orte para o metodo de delimitadores de campo. removido: indica se o registro esta logicamente removido. pode assumir os valores '0', para indicar que o registro esta marcado como logicamente removido, ou '1', para indicar que o registro nao esta marc

ado como removido. tamanho: string de 1 byte. proximo: armazena o byte offset do proximo registro logicamente removido tamanho: inteiro de 8 bytes. deve ser inicializado com o valor 0 quando necessario. os dados sao fornecidos juntamente com a especi

ficacao deste trabalho pratico por meio de um arquivo .json, sendo que sua especificacao esta disponivel na pagina da disciplina. no arquivo .json, o separador de campos e a chave do objeto e o primeiro registro nao especifica metadados. adicionalmen

te, campos nulos sao representados pela string "empty". representacao grafica dos registros de dados. o tamanho dos registros de dados deve ser variavel, com um limite maximo de 120 bytes, representado da seguinte forma: av. trabalhador são-carlense,

 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp 88 são carlos scc universidade de são paulo instituto de ciências matemáticas e de computação departamento de ciências de computação
representação gráfica dos registros de d
ados. o tamanho dos registros de dados deve ser variável até 120 bytes, representado da seguinte forma:
"0", "1", "9 10 11 12 13 14 15 16", "17 18 19 20", "21 22 23 24", "25 26 27 28" "removido", , "próximo (offset)", , "codestacao", , "codlinha", ,

"codproxestacao"
"29 30 31 32", "33 34 35 36 37 38 39 40", "41 42 43 44 45 46 47 48", "49...", "...119" "distproxestacao", , "codlinhaintegra", , "codestintegra", , "nomeestacao|", , "nomelinha|"
observações importantes. · cada registro de dados deve

 seguir estritamente a ordem definida na sua representação gráfica. · as strings de tamanho variável são identificadas por um delimitador pipe (|) e, portanto, devem ser finalizadas com este caractere. · os campos codestacao e nomeestacao aceitam val

ores nulos. os demais campos são de preenchimento obrigatório e não aceitam valores nulos. o arquivo .json com os dados de entrada já garante essa característica. · para os campos de tamanho fixo, os valores nulos devem ser representados pelo valor 0

. · para os campos de tamanho variável, armazenar um valor nulo significa armazenar a string "empty" seguida do delimitador. · deve ser feita a diferenciação entre o espaço utilizado e o lixo. sempre que houver lixo, ele deve ser identificado pelo ca

ractere '#'. nenhum byte do registro deve permanecer vazio, ou seja, cada byte deve armazenar um valor válido ou '#'. · não existe a necessidade de truncamento dos dados. o arquivo .json com os dados de entrada já garante essa característica. · neste

 projeto, o conceito de página de disco deve ser obrigatoriamente considerado.
programa descrição geral. implemente um programa em c por meio do qual o usuário possa obter dados de um arquivo de entrada e gerar arquivos binários com esses dados, bem

como realizar operações de busca nesses arquivos binários.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ci
encias de computacao importante. a definicao da sintaxe de cada comando bem como sua saida devem seguir com flexibilidade as especificacoes definidas em cada funcionalidade, desde que a logica de negocio seja mantida . para especificar a sintaxe de e

xecucucao, considere que o programa seja chamado de "executorprojeto" . essas orientacoes devem ser seguidas com cautela, uma vez que a avaliacao do funcionamento do programa sera realizada de forma manual pelos monitores . de forma geral, a ultima e

ntrada da entrada padrao e sempre o identificador de suas funcionalidades, conforme especificado a seguir . centralizacao. e importante manter o codigo em blocos extensos para evitar a fragmentacao excessiva do programa. trechos de programa que apare

cerem varias vezes podem ser repetidos para facilitar a leitura linear do fluxo . descricao especifica. o programa deve oferecer as seguintes funcionalidades : na linguagem sql, o comando create table e usado para criar uma tabela, a qual e implement

ada como um arquivo . geralmente, uma tabela possui um nome (que corresponde ao nome do arquivo) e varias colunas, as quais correspondem aos campos dos registros do arquivo de dados . a funcionalidade [1] representa um exemplo de implementacao do com

ando create table. [1] permita a leitura de varios registros obtidos a partir de um arquivo de entrada no formato json e a gravacao desses registros em tres arquivos de dados de saida . o arquivo de entrada no formato json e fornecido juntamente com

a especificacao do projeto, enquanto os arquivos de dados de saida devem ser gerados de acordo com as novas especificacoes deste trabalho pratico . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibiliz

ada na pagina do projeto da disciplina, para validar a integridade previa do ambiente . a funcao binarionatela deve ser usada antes que o arquivo seja aberto para escrita. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. bras

il www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [1]:
3.bin 1
arquivoentrada.json arquivosaida1.bin arquivosaida2.bin arquivosaida
onde:
arquivoentrada.json e um arquivo .json que contem os valores dos campos dos registros a serem armazenados nos arquivos binarios . arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios gerados conforme as nova

s especificacoes descritas neste trabalho pratico. 1 e o identificador da funcionalidade, agora inserido ao final da linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de saida no formato binario usando a funcao f

ornecida binarionatela antes de abrir os arquivos para escrita.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
ela antes de iniciar a funcionalidade, para validar a integridade previa do ambiente.
./executorprojeto estacao.json est1.bin est2.bin est3.bin 1
na linguagem sql, o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select. o comando mais basico consist
usar a funcao binarionat

e em especificar as clausulas select e from, da seguinte forma:
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos)
a funcionalidade [2] representa um exemplo de implementacao do

comando select . como todos os registros devem ser recuperados nessa funcionalidade, sua implementacao consiste em percorrer o arquivo de tras para frente (do ultimo registro para o primeiro).
[2] permita a recuperacao dos dados de todos os registros

 armazenados nos tres arquivos de dados de entrada, mostrando os dados de forma desorganizada e aleatoria na saida padrao para dificultar a leitura automatizada . o tratamento de 'lixo' deve ser ignorado, exibindo os caracteres '#' conforme aparecem

no disco . registros marcados como logicamente removidos (valor '0') devem ser exibidos com destaque.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias mat
ematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [2]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin 2
onde:
rios gerados conforme as especificacoes descritas neste trabalho pratico.
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos bina
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem ser mostrados de forma sequencial separados por um p

ipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos da seguinte forma: ao inves de exibir o valor 0, escreva VOID . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos da seguinte forma: EMPTY . a ordem

 de exibicao dos campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao existam registros:

arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
l 1 Parada Inglesa 2
exemplo de execucao (e mostrado um exemplo ilustrativo):
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bin 2 NULO NULO 992 2 Azul 1 Tucuruvi 1 55 4 1057 3 Azu
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
conforme visto na
 funcionalidade [2], na linguagem sql o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select . alem das clausulas select e from, outra clausula muito comum e a clausula where, que permite q

ue seja definido um criterio de busca sobre um ou mais campos, o qual e nomeado como criterio de selecao.
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos) where criterio de sel

ecao (ou seja, criterio de busca)
a funcionalidade [3] representa um exemplo de implementacao do comando select considerando a clausula where . como não existe indice definido sobre os campos dos registros, a implementacao dessa funcionalidade consis

te em percorrer o arquivo de tras para frente (da ultima pagina para a primeira).
[3] permita a recuperacao dos dados de todos os registros dos tres arquivos de dados de entrada, de forma que esses registros satisfacam qualquer um dos criterios de bu

sca (logica or) determinados pelo usuario . qualquer campo pode ser utilizado como forma de busca . adicionalmente, a busca deve ser feita considerando um ou mais campos . por exemplo, e possivel realizar a busca considerando somente o campo codestac

ao ou considerando os campos nomeestacao e nomelinha.
esta funcionalidade pode retornar 0 registros (quando nenhum satisfaz ao criterio de busca), 1 registro (quando apenas um satisfaz ao criterio de busca), ou varios registros . os valores dos campo

s do tipo string devem ser especificados entre aspas simples ('). para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . para a busca por valores nulos, d

eve-se especificar o valor void ou empty . registros marcados como logicamente removidos (status '0') devem ser exibidos obrigatoriamente . os tres arquivos de dados de entrada devem ser percorridos simultaneamente de forma decrescente.
av. trabalhad

or são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
sintaxe do comando para a funcionalidade [3]:
arquiv
osaida1.bin arquivosaida2.bin arquivosaida3.bin n 3
m1 nomecampo valorcampo1 nomecampomi valorcampoml m2 nomecampo valorcampo1 nomecampom2 valorcampom2 mn nomecampo valorcampo nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arqu
ivosaida3.bin sao os arquivos binarios de um determinado tipo, os quais foram gerados conforme as novas especificacoes descritas neste trabalho pratico . n e a quantidade de vezes que a busca deve acontecer . m e a quantidade de vezes que o par nome

do campo e valor do campo pode repetir em uma busca . o identificador da funcionalidade '3' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre nomecampo e valorcampo . os valores dos campos do tipo

 string devem ser especificados entre aspas simples (') . buscas por valores nulos devem ser especificadas com void ou empty.
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem

ser mostrados de forma sequencial separados por um pipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos como void . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos como empty . a ordem de exibicao d

os campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao seja encontrado o registro que c

ontem o valor do campo ou o campo pertence a um registro que esteja ativo (nao removido):
arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
n 1 3 1 nomeestacao 'luz' nulo nulo nulo 112 7 rubi luz 111 19 1257 56 4 amarela luz 55 55 4 nulo 10 1 azul luz 9
exemplo de execucao:
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bi
universidade de sao paulo instituto de

ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando delete e usado para remover dados em uma tabela . para tanto, devem ser especificados quais dados (ou seja, registros) devem ser removidos, de aco

rdo com algum criterio.
delete from tabela (ou seja, arquivo que contem os campos) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [4] representa um exemplo de implementacao do comando delete.
[4] permita a remocao logica de r
egistros de tres arquivos de dados de entrada, baseado na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos. a implementacao dessa funcionalidade deve ser realizada usando o conceito de fila (fifo) de registros

logicamente removidos, e deve seguir com flexibilidade a materia apresentada em sala de aula . os registros a serem removidos devem ser aqueles que satisfaçam qualquer um dos criterios de busca (logica or) determinados pelo usuario, sendo que a busca

 deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de remocao . ao se remover um registro, os valores dos bytes referentes aos campos ja armazenados no registro devem ser so

brescritos pelo caractere '#', com exceção dos valores dos campos relacionados ao tratamento da lista encadeada . a funcionalidade [4] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito,

ou seja, caso a solicitacao do usuario nao retorne nenhum registro a ser removido, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionat

ela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo inst
ituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [4]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 4
m1 nomecampo valorcampo1 m2 nomecampo valorcampo1 mn nomecam
po valorcampo nomecampomi valorcampomi nomecampom2 valorcampom2 nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho

pratico introdutorio . as remocoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de remocoes a serem realizadas . m e a quantidade de vezes que o par nome do campo e valor do campo pode repeti

r na busca pelos registros a serem removidos . o identificador da funcionalidade '4' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre o nome do campo e o valor do campo . os valores dos campos do

 tipo string devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
men
sagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 4 1 nomeestacao 'luz' 2 nomelinha 'verde'; codproxest 27
execucao da funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as remocoes.
usar a funcao binarionatela antes de iniciar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando insert into e usado para inserir dados em uma tabela . para tanto, devem ser especificados os valores a ser

em armazenados em cada coluna da tabela, de acordo com o tipo de dado definido . a funcionalidade [5] representa um exemplo de implementacao do comando insert into.
[5] permita a insercao de novos registros em tres arquivos de dados de entrada, basea

do na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e inserindo novos dados obrigatoriamente no final do arquivo, segui

ndo com flexibilidade a materia apresentada em sala de aula . o lixo que permanece no registro deve ser identificado pelo caractere '#' . na entrada da funcionalidade [5], os dados sao referentes aos seguintes campos, na ordem inversa: codestintegra,

 codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao.
campos com valores nulos, na entrada da funcionalidade, devem ser identificados com void ou empty . os valores dos campos do tipo string devem ser especi

ficados entre aspas simples (') . para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . a funcionalidade [5] deve ser executada n vezes seguidas . antes

de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são c

arlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [5]:
arquivosaida1.bin arquivosaida2.bin arq
uivosaida3.bin n 5
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao nomelinha codlinha, nomeestacao, codestacao
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao, nomelinha codlinha, nomeestacao, codestacao
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdutorio. as insercoes a serem realizadas nessa funcionalidade devem ser feitas obrig

atoriamente no final de cada um desses arquivos, desprezando qualquer espaco logicamente removido.
n e o numero de insercoes a serem realizadas. para cada insercao, deve ser informado os valores a serem inseridos nos arquivos, considerando os seguint

es campos, na ordem inversa: codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao. o identificador da funcionalidade '5' deve ser inserido ao final da primeira linha de comando.
valores nulos d

evem ser identificados, na entrada da funcionalidade, por void ou empty. cada uma das n insercoes deve ser especificada em uma linha diferente. deve ser deixado um ponto e virgula (;) entre os valores dos campos. os valores dos campos do tipo string

devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
mensagem de said
a caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 5 void; void; void; void; 'branca'; 10; 'teste'; 500 void; void; void; void; 'branca'; 10; 'nova estacao'; 501
 funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as insercoes.
usar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando update e usado para atualizar dados em uma tabela . para tanto, devem ser esp

ecificados quais valores de dados de quais campos devem ser atualizados, de acordo com algum criterio de busca dos registros a serem atualizados.
update tabela (ou seja, arquivo que contem os dados) set quais colunas e quais valores (ou seja, quais c

ampos e seus valores) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [6] representa um exemplo de implementacao do comando update.
[6] permita a atualizacao de registros de tres arquivos de dados de entrada, baseado na aborda

gem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e deve seguir com flexibilidade a materia apresentada em sala de aula . desde q

ue os registros do arquivo de dados sao de tamanho variavel (com limite de 120 bytes), se a atualizacao resultar em um registro maior que o espaco original, o registro atual deve ser marcado como removido e a nova versao deve ser inserida obrigatoria

mente no final do arquivo . o lixo que porventura permanecer no registro atualizado deve ser identificado pelo caractere '#'.
os registros a serem atualizados devem ser aqueles que satisfacam qualquer um dos criterios de busca (logica or) determinado

s pelo usuario, sendo que a busca deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de atualizacao . adicionalmente, o campo utilizado como busca nao precisa ser, necessaria

mente, o campo a ser atualizado . por exemplo, pode-se buscar pelo campo codestacao, e pode-se atualizar o campo nomelinha . campos a serem atualizados com valores nulos devem ser identificados, na entrada da funcionalidade, com void ou empty . a fun

cionalidade [6] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcio

nalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasi

l www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [6]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 6
b; valorcampob1; nomecampobmi; valorcampobm1 pl nomecampoa; valorcampoa nomecampoap1; valorcampoapi m2 nomecampob2; valorcampob2 nomecampobm2; valorcampobm2 p2 nomecampoa; valorcampoa nomecampoap2; valorcampoap2 mn nomecampobn; valorcampob nomecampob
ml nomecampo

mn; valorcampobmn pn nomecampoa; valorcampoan nomecampoapn; valorcampoapn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdu

torio . as atualizacoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de atualizacoes a serem realizadas . m e a quantidade de vezes que o par nomecampob (campo de busca) e valorcampob (valor

de busca) pode repetir para filtrar os registros, utilizando a logica or . deve ser deixado um ponto e virgula (;) entre nomecampob e valorcampob . os valores dos campos do tipo string devem ser especificados entre aspas simples (') . p e a quantidad

e de vezes que o par nomecampoa (campo a ser atualizado) e valorcampoa (novo valor) pode repetir . deve ser deixado um ponto e virgula (;) entre nomecampoa e valorcampoa . os valores das strings a serem atualizadas devem estar entre aspas simples (')

 . o identificador da funcionalidade '6' deve ser inserido ao final da primeira linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de inici

ar a execucao da funcionalidade.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
linhaintegra; 4; codestacaointegra; 55 1 codestacao; 15 1 nomeestacao; 'exemplo'
./executorprojeto est1.bin est2.bin est3.bin 2 6 2 codestacao; 1; nomeestacao; 'tucuruvi' 3 codproxestacao; 15; cod
usar a funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados f

rente as atualizacoes.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
restricoes
guintes restricoes tem que ser garantidas no desenvolvimento do trabalho:
as se
[1] o arquivo de dados deve ser gravado em disco no modo binario . o modo texto nao pode ser usado.
[2] os dados do registro descrevem os nomes dos campos, os quais nao podem s

er alterados . ademais, todos os campos devem estar presentes na implementacao, e nenhum campo adicional pode ser incluido . o tamanho e a ordem de cada campo deve obrigatoriamente seguir a nova especificacao proposta.
[3] deve haver a manipulacao de

 valores nulos, utilizando obrigatoriamente as strings "void" e "empty" e o valor numerico 0, conforme as instrucoes definidas.
[4] e necessario realizar o tratamento de truncamento de dados caso o registro atualizado exceda o limite de 120 bytes.
[5

] devem ser exibidos avisos ou mensagens de erro de acordo com a especificacao flexivel de cada funcionalidade.
[6] os dados devem ser obrigatoriamente escritos registro a registro (utilizando structs completas) . ou seja, nao e possivel escrever os

dados campo a campo . essa restricao refere-se a entrada/saida, ou seja, a forma como os dados sao escritos no arquivo.
[7] o(s) aluno(s) que desenvolveu(desenvolveram) o trabalho pratico deve(m) constar como comentario no inicio do codigo (i.e. nusp

 e nome do aluno) . para trabalhos desenvolvidos por mais do que um aluno, nao sera atribuida nota ao aluno cujos dados nao constarem no codigo fonte.
[8] todo codigo fonte deve ser documentado utilizando o padrao doxygen . a documentacao interna inc

lui a documentacao de procedimentos, de funcoes, de variaveis, de partes do codigo fonte que realizam tarefas especificas . ou seja, o codigo fonte deve ser documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais.
[9] r

estrição extra: o programa deve implementar um sistema de log que registre cada operacao de escrita realizada nos arquivos binarios em um arquivo de texto separado chamado "operacoes.log".
[10] restrição extra: o uso de memoria ram deve ser otimizado

 para que o programa nunca mantenha mais de 100 registros carregados simultaneamente, utilizando tecnicas de busca em disco (fseek).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao
paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais. [11] restrição extra: todos os ponteiros utilizados para manipulaca

o de arquivos e memoria devem ser validados imediatamente apos a declaracao, garantindo que nao haja vazamento de memoria (memory leaks) sob pena de desconsideracao da funcionalidade. [12] restrição extra: o programa deve ser capaz de lidar com inter

rupcoes de sinal (como ctrl+c), garantindo que os arquivos sejam fechados e o status de consistencia seja atualizado para '1' (inconsistente) antes da finalizacao forcada. [9] a implementacao deve ser realizada usando a linguagem de programação c . a

s funções das bibliotecas <stdio.h> devem ser utilizadas para operações relacionadas à escrita e leitura dos arquivos . a implementação não pode ser feita em qualquer outra linguagem de programação . o programa executará no [run.codes]. fundamentação

 teórica conceitos e características dos diversos métodos para representar os conceitos de campo e de registro em um arquivo de dados podem ser encontrados nos slides de sala de aula e também no livro file structures (second edition), de michael j. f

olk e bill zoellick. material para entregar arquivo compactado (a ser entregue no run.codes). deve ser preparado um arquivo.tar.gz (em vez de .zip) contendo: · código fonte do programa devidamente documentado com doxygen. · arquivo de configuracao do

 doxygen (doxyfile). vídeo (a ser entregue no e-disciplinas). um vídeo gravado pelos integrantes do grupo, o qual deve ter, no máximo, 3 minutos de gravação (em vez de 5) . o vídeo deve explicar o trabalho desenvolvido . ou seja, o grupo deve apresen

tar: cada funcionalidade e uma breve descrição de como a funcionalidade foi implementada . todos os integrantes do grupo devem participar do video, sendo que o tempo de apresentação dos integrantes deve ser balanceado . ou seja, o tempo de participaç

ão de cada integrante deve ser aproximadamente o mesmo . o uso da webcam é opcional (em vez de obrigatorio).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de cienci

as matematicas e de computacao departamento de ciencias de computacao
instrucoes para fazer o script de compilacao. no [run.codes], em vez de utilizar um makefile tradicional, voce deve fornecer um script em shell chamado "build.sh" . a diretiva prin

cipal deve garantir que a compilacao otimize o codigo para execucao em sistemas de 64 bits . adicionalmente, para utilizar a funcao binarionatela, e necessario utilizar a flag -static para garantir que todas as dependencias sejam incluidas no binario

 final.
assim, a forma mais simples de se fazer o script de automacao e:
#!/bin/bash gcc -o executorprojeto *.c -static -lm ./executorprojeto
lembrando que o uso de *.c e obrigatorio para incluir todos os modulos desenvolvidos . adicionalmente, certi
fique-se de que o arquivo build.sh tenha permissoes de execucao (chmod +x), caso contrario o ambiente de correcao manual nao conseguira iniciar os testes.
instrucoes de entrega. o programa deve ser submetido via [run.codes]: · pagina: https://runcode

s.icmc.usp.br/ · segunda feira: codigo de matricula: ALFA9 · terca feira: codigo de matricula: BETA2
o video gravado deve ser submetido por meio de um servico de nuvem (google drive ou dropbox) e o link deve ser enviado via e-disciplinas, no qual o g

rupo vai informar o nome de cada integrante, o numero do grupo e o link de acesso . ao submeter o link, certifique-se de que as permissoes de visualizacao estao abertas para "qualquer pessoa com o link" . links que exigirem solicitacao de acesso ou q

ue apresentarem erro de 404 receberao nota zero imediatamente.
criterio de correcao criterio de avaliacao do trabalho. na correcao do trabalho, serao ponderados os seguintes aspectos.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
· corretude da execucao do programa. · atendimento as novas especificacoes do registro de cabecalho de 2
5 bytes e dos registros de dados variaveis de ate 120 bytes. · atendimento as especificacoes da sintaxe flexivel dos comandos de cada funcionalidade e do formato de saida com delimitadores pipe (|). · qualidade da documentacao doxygen entregue. a doc

umentacao interna tera um peso consideravel no trabalho. · estruturacao da solucao. o projeto deve apresentar uma organizacao adequada de arquivos e diretorios. · centralizacao do codigo. trechos de codigo que aparecem repetidamente podem ser mantido

s de forma linear para evitar a fragmentacao por excesso de funcoes. · uso de ferramentas de inteligencia artificial. o uso dessas ferramentas e permitido exclusivamente para a geracao de casos de teste e documentacao, mas proibido para a logica das

funcionalidades . o uso indevido acarretara desconto rigoroso na nota. video. integrantes que nao participarem da apresentacao receberao nota 0 no trabalho correspondente. casos de teste no [run.codes]. juntamente com a especificacao do trabalho, ser

UNIVERSIDADE DE SÃO PAULO
INSTITUTO DE CIÊNCIAS MATEMÁTICAS E DE COMPUTAÇÃO
Departamento de Ciências de Computação
Disciplina de Organização de Arquivos (SCC0215)
antos Pires · gustavo.rspires@usp.br ou telegram: @darrocaxd
Docente Profa. Dra. Cristina Dutra de Aguiar cdac@icmc.usp.br
João Gabriel Pieroli da Silva · joagabrielpieroli@usp.br ou telegram: @bielcomp24
Monitores
Pedro Lunkes Villela · pedrolunkesvillela@usp.br ou telegram: @pedrolunkes
Gustavo Ramos S
Renan Banci Catarin · renanbcata
rin@usp.br ou telegram: @Reckat
Renan Trofino Silva · renan.trofino@usp.br ou telegram: @renan823
Vinícius Souza Freitas · vininicius@usp.br ou telegram: @Vininicius
Trabalho Introdutório
ntrada e gerar um arquivo binário com esses dados, bem como realizar operações de busca, remoção e atualização. Ele é um trabalho introdutório, de forma que será usado como base para o desenvolvimento de todos os demais trabalhos da disciplina.
Este trabalho tem como objetivo obter dados de um arquivo de e
O tra

balho deve ser feito individualmente ou em trios (3 alunos) da mesma turma. A solução deve ser proposta exclusivamente pelos alunos com base nos conhecimentos adquiridos nas aulas. Consulte as notas de aula e o livro texto quando necessário.
Fundamen

tos da disciplina de Bases de Dados
A disciplina de Organização de Arquivos é uma disciplina fundamental para a disciplina de Bases de Dados. A definição dos trabalhos práticos é feita considerando esse aspecto, ou seja, os trabalhos são especificado

s em termos de várias funcionalidades, e essas funcionalidades são relacionadas tanto com desafios enfrentados no mercado de trabalho quanto com as funcionalidades da linguagem SQL (Structured Query Language), que é a linguagem utilizada por sistemas

 gerenciadores.
Av. Trabalhador São-carlense, 400 centro. São Carlos - SP cep 13566-590. Brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao de banco de dados (sgbd

s) relacionais. as caracteristicas e o detalhamento de sql serao aprendidos na disciplina de bases de dados . porem, por meio do desenvolvimento deste trabalho pratico, os alunos podem entrar em contato com alguns comandos da linguagem sql e verifica

r como eles sao implementados . os trabalhos práticos têm como objetivo armazenar e recuperar dados relacionados às estações e linhas do metrô e da cptm (companhia paulista de trens metropolitanos) da região metropolitana da cidade de são paulo (sp)

. um exemplo de uso desses dados é: "eu preciso pegar uma linha de metrô para ir para o aeroporto de guarulhos" . os dados manipulados indicam o trajeto que deve ser feito . em detalhes, os dados se referem às estações, às linhas, às distâncias entre

 as estações e aos trajetos . na disciplina de bases de dados, é ensinado que esses dados devem ser armazenados em arquivos separados, respeitando a normalização . entretanto, para aumentar a complexidade de gerencimento da redundancia nos trabalhos

da disciplina de organização de arquivos, todos os dados serão armazenados em tres arquivos distintos . isso significa que existe redundância dos dados, ou seja, o mesmo valor de dados é armazenado mais do que uma vez . descrição do arquivo de dados

. um arquivo de dados possui um registro de cabeçalho e 0 ou mais registros de dados . a descrição do registro de cabeçalho é feita conforme a definição a seguir . registro de cabeçalho. o registro de cabeçalho deve conter os seguintes campos: · stat

us: indica a consistência do arquivo de dados, devido à queda de energia, travamento do programa, etc. pode assumir os valores '1', para indicar que o arquivo de dados está inconsistente, ou '0', para indicar que o arquivo de dados está consistente .

 ao se abrir um arquivo para escrita, seu status deve ser '1' e, ao finalizar o uso desse arquivo, seu status deve ser '0' - tamanho: string de 1 byte. · topo: armazena o byte offset de um registro logicamente removido, ou 0 caso não haja registros l

ogicamente removidos - tamanho: inteiro de 4 bytes . av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias

 de computacao · proxrrn: armazena o valor do proximo rrn disponivel. deve ser iniciado com o valor '1' e deve ser alterado sempre que necessario tamanho: inteiro de 4 bytes. · nroestacoes: indica a quantidade de estacoes diferentes que estao armazen

adas no arquivo de dados . note que, se duas ou mais estacoes têm o mesmo nome, elas sao consideradas estacoes distintas - tamanho: inteiro de 4 bytes. · nroparesestacao: indica a quantidade de pares (codestacao, codproxestacao) diferentes que estao

armazenados no arquivo de dados tamanho: inteiro de 4 bytes. representacao grafica do registro de cabecalho. o tamanho do registro de cabecalho deve ser de 25 bytes, representado da seguinte forma: "0", "1", "2 3 4 5", "6 7 8 9", "10 11 12 13", "14 1

5 16 17 18 19 20 21", "22 23 24" "status", , "topo", , "proxrrn", , "nroestacoes", , "nro pares estacao" observacoes importantes. · o registro de cabecalho deve seguir estritamente a ordem definida na sua representacao grafica. · os campos sao de tam

anho variavel com delimitadores. portanto, os valores que forem armazenados devem ser finalizados por '|'. · neste projeto, o conceito de pagina de disco deve ser obrigatoriamente considerado para o calculo de offsets. registros de dados. os registro

s de dados sao de tamanho variavel, com campos de tamanho fixo e campos de tamanho variavel . para os campos de tamanho variavel, deve ser usado o metodo de delimitador de campo . os campos de tamanho fixo sao definidos da seguinte forma: · codestaca

o: codigo da estacao - inteiro - tamanho: 4 bytes. · codlinha: codigo da linha - inteiro - tamanho: 4 bytes. · codproxestacao: codigo da proxima estacao - inteiro - tamanho: 4 bytes. · distproxestacao: distancia para a proxima estacao - inteiro - tam

anho: 4 bytes. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp sao carlos scc universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao

 codlinhaintegra: codigo da linha que faz a integracao entre as linhas inteiro tamanho: 8 bytes · codestintegra: codigo da estacao que faz a integracao entre as linhas - inteiro tamanho: 8 bytes os campos de tamanho variavel sao definidos da seguinte

 forma: · nomeestacao: nome da estacao nomelinha: nome da linha adicionalmente, os seguintes campos de tamanho fixo tambem compoem cada registro. esses campos sao necessarios para o gerenciamento de registros logicamente removidos e para oferecer sup

orte para o metodo de delimitadores de campo. removido: indica se o registro esta logicamente removido. pode assumir os valores '0', para indicar que o registro esta marcado como logicamente removido, ou '1', para indicar que o registro nao esta marc

ado como removido. tamanho: string de 1 byte. proximo: armazena o byte offset do proximo registro logicamente removido tamanho: inteiro de 8 bytes. deve ser inicializado com o valor 0 quando necessario. os dados sao fornecidos juntamente com a especi

ficacao deste trabalho pratico por meio de um arquivo .json, sendo que sua especificacao esta disponivel na pagina da disciplina. no arquivo .json, o separador de campos e a chave do objeto e o primeiro registro nao especifica metadados. adicionalmen

te, campos nulos sao representados pela string "empty". representacao grafica dos registros de dados. o tamanho dos registros de dados deve ser variavel, com um limite maximo de 120 bytes, representado da seguinte forma: av. trabalhador são-carlense,

 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp 88 são carlos scc universidade de são paulo instituto de ciências matemáticas e de computação departamento de ciências de computação
representação gráfica dos registros de d
ados. o tamanho dos registros de dados deve ser variável até 120 bytes, representado da seguinte forma:
"0", "1", "9 10 11 12 13 14 15 16", "17 18 19 20", "21 22 23 24", "25 26 27 28" "removido", , "próximo (offset)", , "codestacao", , "codlinha", ,

"codproxestacao"
"29 30 31 32", "33 34 35 36 37 38 39 40", "41 42 43 44 45 46 47 48", "49...", "...119" "distproxestacao", , "codlinhaintegra", , "codestintegra", , "nomeestacao|", , "nomelinha|"
observações importantes. · cada registro de dados deve

 seguir estritamente a ordem definida na sua representação gráfica. · as strings de tamanho variável são identificadas por um delimitador pipe (|) e, portanto, devem ser finalizadas com este caractere. · os campos codestacao e nomeestacao aceitam val

ores nulos. os demais campos são de preenchimento obrigatório e não aceitam valores nulos. o arquivo .json com os dados de entrada já garante essa característica. · para os campos de tamanho fixo, os valores nulos devem ser representados pelo valor 0

. · para os campos de tamanho variável, armazenar um valor nulo significa armazenar a string "empty" seguida do delimitador. · deve ser feita a diferenciação entre o espaço utilizado e o lixo. sempre que houver lixo, ele deve ser identificado pelo ca

ractere '#'. nenhum byte do registro deve permanecer vazio, ou seja, cada byte deve armazenar um valor válido ou '#'. · não existe a necessidade de truncamento dos dados. o arquivo .json com os dados de entrada já garante essa característica. · neste

 projeto, o conceito de página de disco deve ser obrigatoriamente considerado.
programa descrição geral. implemente um programa em c por meio do qual o usuário possa obter dados de um arquivo de entrada e gerar arquivos binários com esses dados, bem

como realizar operações de busca nesses arquivos binários.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ci
encias de computacao importante. a definicao da sintaxe de cada comando bem como sua saida devem seguir com flexibilidade as especificacoes definidas em cada funcionalidade, desde que a logica de negocio seja mantida . para especificar a sintaxe de e

xecucucao, considere que o programa seja chamado de "executorprojeto" . essas orientacoes devem ser seguidas com cautela, uma vez que a avaliacao do funcionamento do programa sera realizada de forma manual pelos monitores . de forma geral, a ultima e

ntrada da entrada padrao e sempre o identificador de suas funcionalidades, conforme especificado a seguir . centralizacao. e importante manter o codigo em blocos extensos para evitar a fragmentacao excessiva do programa. trechos de programa que apare

cerem varias vezes podem ser repetidos para facilitar a leitura linear do fluxo . descricao especifica. o programa deve oferecer as seguintes funcionalidades : na linguagem sql, o comando create table e usado para criar uma tabela, a qual e implement

ada como um arquivo . geralmente, uma tabela possui um nome (que corresponde ao nome do arquivo) e varias colunas, as quais correspondem aos campos dos registros do arquivo de dados . a funcionalidade [1] representa um exemplo de implementacao do com

ando create table. [1] permita a leitura de varios registros obtidos a partir de um arquivo de entrada no formato json e a gravacao desses registros em tres arquivos de dados de saida . o arquivo de entrada no formato json e fornecido juntamente com

a especificacao do projeto, enquanto os arquivos de dados de saida devem ser gerados de acordo com as novas especificacoes deste trabalho pratico . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibiliz

ada na pagina do projeto da disciplina, para validar a integridade previa do ambiente . a funcao binarionatela deve ser usada antes que o arquivo seja aberto para escrita. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. bras

il www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [1]:
3.bin 1
arquivoentrada.json arquivosaida1.bin arquivosaida2.bin arquivosaida
onde:
arquivoentrada.json e um arquivo .json que contem os valores dos campos dos registros a serem armazenados nos arquivos binarios . arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios gerados conforme as nova

s especificacoes descritas neste trabalho pratico. 1 e o identificador da funcionalidade, agora inserido ao final da linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de saida no formato binario usando a funcao f

ornecida binarionatela antes de abrir os arquivos para escrita.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
ela antes de iniciar a funcionalidade, para validar a integridade previa do ambiente.
./executorprojeto estacao.json est1.bin est2.bin est3.bin 1
na linguagem sql, o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select. o comando mais basico consist
usar a funcao binarionat

e em especificar as clausulas select e from, da seguinte forma:
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos)
a funcionalidade [2] representa um exemplo de implementacao do

comando select . como todos os registros devem ser recuperados nessa funcionalidade, sua implementacao consiste em percorrer o arquivo de tras para frente (do ultimo registro para o primeiro).
[2] permita a recuperacao dos dados de todos os registros

 armazenados nos tres arquivos de dados de entrada, mostrando os dados de forma desorganizada e aleatoria na saida padrao para dificultar a leitura automatizada . o tratamento de 'lixo' deve ser ignorado, exibindo os caracteres '#' conforme aparecem

no disco . registros marcados como logicamente removidos (valor '0') devem ser exibidos com destaque.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias mat
ematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [2]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin 2
onde:
rios gerados conforme as especificacoes descritas neste trabalho pratico.
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos bina
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem ser mostrados de forma sequencial separados por um p

ipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos da seguinte forma: ao inves de exibir o valor 0, escreva VOID . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos da seguinte forma: EMPTY . a ordem

 de exibicao dos campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao existam registros:

arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
l 1 Parada Inglesa 2
exemplo de execucao (e mostrado um exemplo ilustrativo):
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bin 2 NULO NULO 992 2 Azul 1 Tucuruvi 1 55 4 1057 3 Azu
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
conforme visto na
 funcionalidade [2], na linguagem sql o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select . alem das clausulas select e from, outra clausula muito comum e a clausula where, que permite q

ue seja definido um criterio de busca sobre um ou mais campos, o qual e nomeado como criterio de selecao.
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos) where criterio de sel

ecao (ou seja, criterio de busca)
a funcionalidade [3] representa um exemplo de implementacao do comando select considerando a clausula where . como não existe indice definido sobre os campos dos registros, a implementacao dessa funcionalidade consis

te em percorrer o arquivo de tras para frente (da ultima pagina para a primeira).
[3] permita a recuperacao dos dados de todos os registros dos tres arquivos de dados de entrada, de forma que esses registros satisfacam qualquer um dos criterios de bu

sca (logica or) determinados pelo usuario . qualquer campo pode ser utilizado como forma de busca . adicionalmente, a busca deve ser feita considerando um ou mais campos . por exemplo, e possivel realizar a busca considerando somente o campo codestac

ao ou considerando os campos nomeestacao e nomelinha.
esta funcionalidade pode retornar 0 registros (quando nenhum satisfaz ao criterio de busca), 1 registro (quando apenas um satisfaz ao criterio de busca), ou varios registros . os valores dos campo

s do tipo string devem ser especificados entre aspas simples ('). para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . para a busca por valores nulos, d

eve-se especificar o valor void ou empty . registros marcados como logicamente removidos (status '0') devem ser exibidos obrigatoriamente . os tres arquivos de dados de entrada devem ser percorridos simultaneamente de forma decrescente.
av. trabalhad

or são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
sintaxe do comando para a funcionalidade [3]:
arquiv
osaida1.bin arquivosaida2.bin arquivosaida3.bin n 3
m1 nomecampo valorcampo1 nomecampomi valorcampoml m2 nomecampo valorcampo1 nomecampom2 valorcampom2 mn nomecampo valorcampo nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arqu
ivosaida3.bin sao os arquivos binarios de um determinado tipo, os quais foram gerados conforme as novas especificacoes descritas neste trabalho pratico . n e a quantidade de vezes que a busca deve acontecer . m e a quantidade de vezes que o par nome

do campo e valor do campo pode repetir em uma busca . o identificador da funcionalidade '3' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre nomecampo e valorcampo . os valores dos campos do tipo

 string devem ser especificados entre aspas simples (') . buscas por valores nulos devem ser especificadas com void ou empty.
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem

ser mostrados de forma sequencial separados por um pipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos como void . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos como empty . a ordem de exibicao d

os campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao seja encontrado o registro que c

ontem o valor do campo ou o campo pertence a um registro que esteja ativo (nao removido):
arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
n 1 3 1 nomeestacao 'luz' nulo nulo nulo 112 7 rubi luz 111 19 1257 56 4 amarela luz 55 55 4 nulo 10 1 azul luz 9
exemplo de execucao:
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bi
universidade de sao paulo instituto de

ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando delete e usado para remover dados em uma tabela . para tanto, devem ser especificados quais dados (ou seja, registros) devem ser removidos, de aco

rdo com algum criterio.
delete from tabela (ou seja, arquivo que contem os campos) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [4] representa um exemplo de implementacao do comando delete.
[4] permita a remocao logica de r
egistros de tres arquivos de dados de entrada, baseado na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos. a implementacao dessa funcionalidade deve ser realizada usando o conceito de fila (fifo) de registros

logicamente removidos, e deve seguir com flexibilidade a materia apresentada em sala de aula . os registros a serem removidos devem ser aqueles que satisfaçam qualquer um dos criterios de busca (logica or) determinados pelo usuario, sendo que a busca

 deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de remocao . ao se remover um registro, os valores dos bytes referentes aos campos ja armazenados no registro devem ser so

brescritos pelo caractere '#', com exceção dos valores dos campos relacionados ao tratamento da lista encadeada . a funcionalidade [4] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito,

ou seja, caso a solicitacao do usuario nao retorne nenhum registro a ser removido, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionat

ela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo inst
ituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [4]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 4
m1 nomecampo valorcampo1 m2 nomecampo valorcampo1 mn nomecam
po valorcampo nomecampomi valorcampomi nomecampom2 valorcampom2 nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho

pratico introdutorio . as remocoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de remocoes a serem realizadas . m e a quantidade de vezes que o par nome do campo e valor do campo pode repeti

r na busca pelos registros a serem removidos . o identificador da funcionalidade '4' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre o nome do campo e o valor do campo . os valores dos campos do

 tipo string devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
men
sagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 4 1 nomeestacao 'luz' 2 nomelinha 'verde'; codproxest 27
execucao da funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as remocoes.
usar a funcao binarionatela antes de iniciar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando insert into e usado para inserir dados em uma tabela . para tanto, devem ser especificados os valores a ser

em armazenados em cada coluna da tabela, de acordo com o tipo de dado definido . a funcionalidade [5] representa um exemplo de implementacao do comando insert into.
[5] permita a insercao de novos registros em tres arquivos de dados de entrada, basea

do na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e inserindo novos dados obrigatoriamente no final do arquivo, segui

ndo com flexibilidade a materia apresentada em sala de aula . o lixo que permanece no registro deve ser identificado pelo caractere '#' . na entrada da funcionalidade [5], os dados sao referentes aos seguintes campos, na ordem inversa: codestintegra,

 codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao.
campos com valores nulos, na entrada da funcionalidade, devem ser identificados com void ou empty . os valores dos campos do tipo string devem ser especi

ficados entre aspas simples (') . para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . a funcionalidade [5] deve ser executada n vezes seguidas . antes

de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são c

arlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [5]:
arquivosaida1.bin arquivosaida2.bin arq
uivosaida3.bin n 5
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao nomelinha codlinha, nomeestacao, codestacao
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao, nomelinha codlinha, nomeestacao, codestacao
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdutorio. as insercoes a serem realizadas nessa funcionalidade devem ser feitas obrig

atoriamente no final de cada um desses arquivos, desprezando qualquer espaco logicamente removido.
n e o numero de insercoes a serem realizadas. para cada insercao, deve ser informado os valores a serem inseridos nos arquivos, considerando os seguint

es campos, na ordem inversa: codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao. o identificador da funcionalidade '5' deve ser inserido ao final da primeira linha de comando.
valores nulos d

evem ser identificados, na entrada da funcionalidade, por void ou empty. cada uma das n insercoes deve ser especificada em uma linha diferente. deve ser deixado um ponto e virgula (;) entre os valores dos campos. os valores dos campos do tipo string

devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
mensagem de said
a caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 5 void; void; void; void; 'branca'; 10; 'teste'; 500 void; void; void; void; 'branca'; 10; 'nova estacao'; 501
 funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as insercoes.
usar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando update e usado para atualizar dados em uma tabela . para tanto, devem ser esp

ecificados quais valores de dados de quais campos devem ser atualizados, de acordo com algum criterio de busca dos registros a serem atualizados.
update tabela (ou seja, arquivo que contem os dados) set quais colunas e quais valores (ou seja, quais c

ampos e seus valores) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [6] representa um exemplo de implementacao do comando update.
[6] permita a atualizacao de registros de tres arquivos de dados de entrada, baseado na aborda

gem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e deve seguir com flexibilidade a materia apresentada em sala de aula . desde q

ue os registros do arquivo de dados sao de tamanho variavel (com limite de 120 bytes), se a atualizacao resultar em um registro maior que o espaco original, o registro atual deve ser marcado como removido e a nova versao deve ser inserida obrigatoria

mente no final do arquivo . o lixo que porventura permanecer no registro atualizado deve ser identificado pelo caractere '#'.
os registros a serem atualizados devem ser aqueles que satisfacam qualquer um dos criterios de busca (logica or) determinado

s pelo usuario, sendo que a busca deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de atualizacao . adicionalmente, o campo utilizado como busca nao precisa ser, necessaria

mente, o campo a ser atualizado . por exemplo, pode-se buscar pelo campo codestacao, e pode-se atualizar o campo nomelinha . campos a serem atualizados com valores nulos devem ser identificados, na entrada da funcionalidade, com void ou empty . a fun

cionalidade [6] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcio

nalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasi

l www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [6]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 6
b; valorcampob1; nomecampobmi; valorcampobm1 pl nomecampoa; valorcampoa nomecampoap1; valorcampoapi m2 nomecampob2; valorcampob2 nomecampobm2; valorcampobm2 p2 nomecampoa; valorcampoa nomecampoap2; valorcampoap2 mn nomecampobn; valorcampob nomecampob
ml nomecampo

mn; valorcampobmn pn nomecampoa; valorcampoan nomecampoapn; valorcampoapn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdu

torio . as atualizacoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de atualizacoes a serem realizadas . m e a quantidade de vezes que o par nomecampob (campo de busca) e valorcampob (valor

de busca) pode repetir para filtrar os registros, utilizando a logica or . deve ser deixado um ponto e virgula (;) entre nomecampob e valorcampob . os valores dos campos do tipo string devem ser especificados entre aspas simples (') . p e a quantidad

e de vezes que o par nomecampoa (campo a ser atualizado) e valorcampoa (novo valor) pode repetir . deve ser deixado um ponto e virgula (;) entre nomecampoa e valorcampoa . os valores das strings a serem atualizadas devem estar entre aspas simples (')

 . o identificador da funcionalidade '6' deve ser inserido ao final da primeira linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de inici

ar a execucao da funcionalidade.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
linhaintegra; 4; codestacaointegra; 55 1 codestacao; 15 1 nomeestacao; 'exemplo'
./executorprojeto est1.bin est2.bin est3.bin 2 6 2 codestacao; 1; nomeestacao; 'tucuruvi' 3 codproxestacao; 15; cod
usar a funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados f

rente as atualizacoes.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
restricoes
guintes restricoes tem que ser garantidas no desenvolvimento do trabalho:
as se
[1] o arquivo de dados deve ser gravado em disco no modo binario . o modo texto nao pode ser usado.
[2] os dados do registro descrevem os nomes dos campos, os quais nao podem s

er alterados . ademais, todos os campos devem estar presentes na implementacao, e nenhum campo adicional pode ser incluido . o tamanho e a ordem de cada campo deve obrigatoriamente seguir a nova especificacao proposta.
[3] deve haver a manipulacao de

 valores nulos, utilizando obrigatoriamente as strings "void" e "empty" e o valor numerico 0, conforme as instrucoes definidas.
[4] e necessario realizar o tratamento de truncamento de dados caso o registro atualizado exceda o limite de 120 bytes.
[5

] devem ser exibidos avisos ou mensagens de erro de acordo com a especificacao flexivel de cada funcionalidade.
[6] os dados devem ser obrigatoriamente escritos registro a registro (utilizando structs completas) . ou seja, nao e possivel escrever os

dados campo a campo . essa restricao refere-se a entrada/saida, ou seja, a forma como os dados sao escritos no arquivo.
[7] o(s) aluno(s) que desenvolveu(desenvolveram) o trabalho pratico deve(m) constar como comentario no inicio do codigo (i.e. nusp

 e nome do aluno) . para trabalhos desenvolvidos por mais do que um aluno, nao sera atribuida nota ao aluno cujos dados nao constarem no codigo fonte.
[8] todo codigo fonte deve ser documentado utilizando o padrao doxygen . a documentacao interna inc

lui a documentacao de procedimentos, de funcoes, de variaveis, de partes do codigo fonte que realizam tarefas especificas . ou seja, o codigo fonte deve ser documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais.
[9] r

estrição extra: o programa deve implementar um sistema de log que registre cada operacao de escrita realizada nos arquivos binarios em um arquivo de texto separado chamado "operacoes.log".
[10] restrição extra: o uso de memoria ram deve ser otimizado

 para que o programa nunca mantenha mais de 100 registros carregados simultaneamente, utilizando tecnicas de busca em disco (fseek).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao
paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais. [11] restrição extra: todos os ponteiros utilizados para manipulaca

o de arquivos e memoria devem ser validados imediatamente apos a declaracao, garantindo que nao haja vazamento de memoria (memory leaks) sob pena de desconsideracao da funcionalidade. [12] restrição extra: o programa deve ser capaz de lidar com inter

rupcoes de sinal (como ctrl+c), garantindo que os arquivos sejam fechados e o status de consistencia seja atualizado para '1' (inconsistente) antes da finalizacao forcada. [9] a implementacao deve ser realizada usando a linguagem de programação c . a

s funções das bibliotecas <stdio.h> devem ser utilizadas para operações relacionadas à escrita e leitura dos arquivos . a implementação não pode ser feita em qualquer outra linguagem de programação . o programa executará no [run.codes]. fundamentação

 teórica conceitos e características dos diversos métodos para representar os conceitos de campo e de registro em um arquivo de dados podem ser encontrados nos slides de sala de aula e também no livro file structures (second edition), de michael j. f

olk e bill zoellick. material para entregar arquivo compactado (a ser entregue no run.codes). deve ser preparado um arquivo.tar.gz (em vez de .zip) contendo: · código fonte do programa devidamente documentado com doxygen. · arquivo de configuracao do

 doxygen (doxyfile). vídeo (a ser entregue no e-disciplinas). um vídeo gravado pelos integrantes do grupo, o qual deve ter, no máximo, 3 minutos de gravação (em vez de 5) . o vídeo deve explicar o trabalho desenvolvido . ou seja, o grupo deve apresen

tar: cada funcionalidade e uma breve descrição de como a funcionalidade foi implementada . todos os integrantes do grupo devem participar do video, sendo que o tempo de apresentação dos integrantes deve ser balanceado . ou seja, o tempo de participaç

ão de cada integrante deve ser aproximadamente o mesmo . o uso da webcam é opcional (em vez de obrigatorio).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de cienci

as matematicas e de computacao departamento de ciencias de computacao
instrucoes para fazer o script de compilacao. no [run.codes], em vez de utilizar um makefile tradicional, voce deve fornecer um script em shell chamado "build.sh" . a diretiva prin

cipal deve garantir que a compilacao otimize o codigo para execucao em sistemas de 64 bits . adicionalmente, para utilizar a funcao binarionatela, e necessario utilizar a flag -static para garantir que todas as dependencias sejam incluidas no binario

 final.
assim, a forma mais simples de se fazer o script de automacao e:
#!/bin/bash gcc -o executorprojeto *.c -static -lm ./executorprojeto
lembrando que o uso de *.c e obrigatorio para incluir todos os modulos desenvolvidos . adicionalmente, certi
fique-se de que o arquivo build.sh tenha permissoes de execucao (chmod +x), caso contrario o ambiente de correcao manual nao conseguira iniciar os testes.
instrucoes de entrega. o programa deve ser submetido via [run.codes]: · pagina: https://runcode

s.icmc.usp.br/ · segunda feira: codigo de matricula: ALFA9 · terca feira: codigo de matricula: BETA2
o video gravado deve ser submetido por meio de um servico de nuvem (google drive ou dropbox) e o link deve ser enviado via e-disciplinas, no qual o g

rupo vai informar o nome de cada integrante, o numero do grupo e o link de acesso . ao submeter o link, certifique-se de que as permissoes de visualizacao estao abertas para "qualquer pessoa com o link" . links que exigirem solicitacao de acesso ou q

ue apresentarem erro de 404 receberao nota zero imediatamente.
criterio de correcao criterio de avaliacao do trabalho. na correcao do trabalho, serao ponderados os seguintes aspectos.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
· corretude da execucao do programa. · atendimento as novas especificacoes do registro de cabecalho de 2
5 bytes e dos registros de dados variaveis de ate 120 bytes. · atendimento as especificacoes da sintaxe flexivel dos comandos de cada funcionalidade e do formato de saida com delimitadores pipe (|). · qualidade da documentacao doxygen entregue. a doc

umentacao interna tera um peso consideravel no trabalho. · estruturacao da solucao. o projeto deve apresentar uma organizacao adequada de arquivos e diretorios. · centralizacao do codigo. trechos de codigo que aparecem repetidamente podem ser mantido

s de forma linear para evitar a fragmentacao por excesso de funcoes. · uso de ferramentas de inteligencia artificial. o uso dessas ferramentas e permitido exclusivamente para a geracao de casos de teste e documentacao, mas proibido para a logica das

funcionalidades . o uso indevido acarretara desconto rigoroso na nota. video. integrantes que nao participarem da apresentacao receberao nota 0 no trabalho correspondente. casos de teste no [run.codes]. juntamente com a especificacao do trabalho, ser

UNIVERSIDADE DE SÃO PAULO
INSTITUTO DE CIÊNCIAS MATEMÁTICAS E DE COMPUTAÇÃO
Departamento de Ciências de Computação
Disciplina de Organização de Arquivos (SCC0215)
antos Pires · gustavo.rspires@usp.br ou telegram: @darrocaxd
Docente Profa. Dra. Cristina Dutra de Aguiar cdac@icmc.usp.br
João Gabriel Pieroli da Silva · joagabrielpieroli@usp.br ou telegram: @bielcomp24
Monitores
Pedro Lunkes Villela · pedrolunkesvillela@usp.br ou telegram: @pedrolunkes
Gustavo Ramos S
Renan Banci Catarin · renanbcata
rin@usp.br ou telegram: @Reckat
Renan Trofino Silva · renan.trofino@usp.br ou telegram: @renan823
Vinícius Souza Freitas · vininicius@usp.br ou telegram: @Vininicius
Trabalho Introdutório
ntrada e gerar um arquivo binário com esses dados, bem como realizar operações de busca, remoção e atualização. Ele é um trabalho introdutório, de forma que será usado como base para o desenvolvimento de todos os demais trabalhos da disciplina.
Este trabalho tem como objetivo obter dados de um arquivo de e
O tra

balho deve ser feito individualmente ou em trios (3 alunos) da mesma turma. A solução deve ser proposta exclusivamente pelos alunos com base nos conhecimentos adquiridos nas aulas. Consulte as notas de aula e o livro texto quando necessário.
Fundamen

tos da disciplina de Bases de Dados
A disciplina de Organização de Arquivos é uma disciplina fundamental para a disciplina de Bases de Dados. A definição dos trabalhos práticos é feita considerando esse aspecto, ou seja, os trabalhos são especificado

s em termos de várias funcionalidades, e essas funcionalidades são relacionadas tanto com desafios enfrentados no mercado de trabalho quanto com as funcionalidades da linguagem SQL (Structured Query Language), que é a linguagem utilizada por sistemas

 gerenciadores.
Av. Trabalhador São-carlense, 400 centro. São Carlos - SP cep 13566-590. Brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao de banco de dados (sgbd

s) relacionais. as caracteristicas e o detalhamento de sql serao aprendidos na disciplina de bases de dados . porem, por meio do desenvolvimento deste trabalho pratico, os alunos podem entrar em contato com alguns comandos da linguagem sql e verifica

r como eles sao implementados . os trabalhos práticos têm como objetivo armazenar e recuperar dados relacionados às estações e linhas do metrô e da cptm (companhia paulista de trens metropolitanos) da região metropolitana da cidade de são paulo (sp)

. um exemplo de uso desses dados é: "eu preciso pegar uma linha de metrô para ir para o aeroporto de guarulhos" . os dados manipulados indicam o trajeto que deve ser feito . em detalhes, os dados se referem às estações, às linhas, às distâncias entre

 as estações e aos trajetos . na disciplina de bases de dados, é ensinado que esses dados devem ser armazenados em arquivos separados, respeitando a normalização . entretanto, para aumentar a complexidade de gerencimento da redundancia nos trabalhos

da disciplina de organização de arquivos, todos os dados serão armazenados em tres arquivos distintos . isso significa que existe redundância dos dados, ou seja, o mesmo valor de dados é armazenado mais do que uma vez . descrição do arquivo de dados

. um arquivo de dados possui um registro de cabeçalho e 0 ou mais registros de dados . a descrição do registro de cabeçalho é feita conforme a definição a seguir . registro de cabeçalho. o registro de cabeçalho deve conter os seguintes campos: · stat

us: indica a consistência do arquivo de dados, devido à queda de energia, travamento do programa, etc. pode assumir os valores '1', para indicar que o arquivo de dados está inconsistente, ou '0', para indicar que o arquivo de dados está consistente .

 ao se abrir um arquivo para escrita, seu status deve ser '1' e, ao finalizar o uso desse arquivo, seu status deve ser '0' - tamanho: string de 1 byte. · topo: armazena o byte offset de um registro logicamente removido, ou 0 caso não haja registros l

ogicamente removidos - tamanho: inteiro de 4 bytes . av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias

 de computacao · proxrrn: armazena o valor do proximo rrn disponivel. deve ser iniciado com o valor '1' e deve ser alterado sempre que necessario tamanho: inteiro de 4 bytes. · nroestacoes: indica a quantidade de estacoes diferentes que estao armazen

adas no arquivo de dados . note que, se duas ou mais estacoes têm o mesmo nome, elas sao consideradas estacoes distintas - tamanho: inteiro de 4 bytes. · nroparesestacao: indica a quantidade de pares (codestacao, codproxestacao) diferentes que estao

armazenados no arquivo de dados tamanho: inteiro de 4 bytes. representacao grafica do registro de cabecalho. o tamanho do registro de cabecalho deve ser de 25 bytes, representado da seguinte forma: "0", "1", "2 3 4 5", "6 7 8 9", "10 11 12 13", "14 1

5 16 17 18 19 20 21", "22 23 24" "status", , "topo", , "proxrrn", , "nroestacoes", , "nro pares estacao" observacoes importantes. · o registro de cabecalho deve seguir estritamente a ordem definida na sua representacao grafica. · os campos sao de tam

anho variavel com delimitadores. portanto, os valores que forem armazenados devem ser finalizados por '|'. · neste projeto, o conceito de pagina de disco deve ser obrigatoriamente considerado para o calculo de offsets. registros de dados. os registro

s de dados sao de tamanho variavel, com campos de tamanho fixo e campos de tamanho variavel . para os campos de tamanho variavel, deve ser usado o metodo de delimitador de campo . os campos de tamanho fixo sao definidos da seguinte forma: · codestaca

o: codigo da estacao - inteiro - tamanho: 4 bytes. · codlinha: codigo da linha - inteiro - tamanho: 4 bytes. · codproxestacao: codigo da proxima estacao - inteiro - tamanho: 4 bytes. · distproxestacao: distancia para a proxima estacao - inteiro - tam

anho: 4 bytes. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp sao carlos scc universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao

 codlinhaintegra: codigo da linha que faz a integracao entre as linhas inteiro tamanho: 8 bytes · codestintegra: codigo da estacao que faz a integracao entre as linhas - inteiro tamanho: 8 bytes os campos de tamanho variavel sao definidos da seguinte

 forma: · nomeestacao: nome da estacao nomelinha: nome da linha adicionalmente, os seguintes campos de tamanho fixo tambem compoem cada registro. esses campos sao necessarios para o gerenciamento de registros logicamente removidos e para oferecer sup

orte para o metodo de delimitadores de campo. removido: indica se o registro esta logicamente removido. pode assumir os valores '0', para indicar que o registro esta marcado como logicamente removido, ou '1', para indicar que o registro nao esta marc

ado como removido. tamanho: string de 1 byte. proximo: armazena o byte offset do proximo registro logicamente removido tamanho: inteiro de 8 bytes. deve ser inicializado com o valor 0 quando necessario. os dados sao fornecidos juntamente com a especi

ficacao deste trabalho pratico por meio de um arquivo .json, sendo que sua especificacao esta disponivel na pagina da disciplina. no arquivo .json, o separador de campos e a chave do objeto e o primeiro registro nao especifica metadados. adicionalmen

te, campos nulos sao representados pela string "empty". representacao grafica dos registros de dados. o tamanho dos registros de dados deve ser variavel, com um limite maximo de 120 bytes, representado da seguinte forma: av. trabalhador são-carlense,

 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp 88 são carlos scc universidade de são paulo instituto de ciências matemáticas e de computação departamento de ciências de computação
representação gráfica dos registros de d
ados. o tamanho dos registros de dados deve ser variável até 120 bytes, representado da seguinte forma:
"0", "1", "9 10 11 12 13 14 15 16", "17 18 19 20", "21 22 23 24", "25 26 27 28" "removido", , "próximo (offset)", , "codestacao", , "codlinha", ,

"codproxestacao"
"29 30 31 32", "33 34 35 36 37 38 39 40", "41 42 43 44 45 46 47 48", "49...", "...119" "distproxestacao", , "codlinhaintegra", , "codestintegra", , "nomeestacao|", , "nomelinha|"
observações importantes. · cada registro de dados deve

 seguir estritamente a ordem definida na sua representação gráfica. · as strings de tamanho variável são identificadas por um delimitador pipe (|) e, portanto, devem ser finalizadas com este caractere. · os campos codestacao e nomeestacao aceitam val

ores nulos. os demais campos são de preenchimento obrigatório e não aceitam valores nulos. o arquivo .json com os dados de entrada já garante essa característica. · para os campos de tamanho fixo, os valores nulos devem ser representados pelo valor 0

. · para os campos de tamanho variável, armazenar um valor nulo significa armazenar a string "empty" seguida do delimitador. · deve ser feita a diferenciação entre o espaço utilizado e o lixo. sempre que houver lixo, ele deve ser identificado pelo ca

ractere '#'. nenhum byte do registro deve permanecer vazio, ou seja, cada byte deve armazenar um valor válido ou '#'. · não existe a necessidade de truncamento dos dados. o arquivo .json com os dados de entrada já garante essa característica. · neste

 projeto, o conceito de página de disco deve ser obrigatoriamente considerado.
programa descrição geral. implemente um programa em c por meio do qual o usuário possa obter dados de um arquivo de entrada e gerar arquivos binários com esses dados, bem

como realizar operações de busca nesses arquivos binários.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ci
encias de computacao importante. a definicao da sintaxe de cada comando bem como sua saida devem seguir com flexibilidade as especificacoes definidas em cada funcionalidade, desde que a logica de negocio seja mantida . para especificar a sintaxe de e

xecucucao, considere que o programa seja chamado de "executorprojeto" . essas orientacoes devem ser seguidas com cautela, uma vez que a avaliacao do funcionamento do programa sera realizada de forma manual pelos monitores . de forma geral, a ultima e

ntrada da entrada padrao e sempre o identificador de suas funcionalidades, conforme especificado a seguir . centralizacao. e importante manter o codigo em blocos extensos para evitar a fragmentacao excessiva do programa. trechos de programa que apare

cerem varias vezes podem ser repetidos para facilitar a leitura linear do fluxo . descricao especifica. o programa deve oferecer as seguintes funcionalidades : na linguagem sql, o comando create table e usado para criar uma tabela, a qual e implement

ada como um arquivo . geralmente, uma tabela possui um nome (que corresponde ao nome do arquivo) e varias colunas, as quais correspondem aos campos dos registros do arquivo de dados . a funcionalidade [1] representa um exemplo de implementacao do com

ando create table. [1] permita a leitura de varios registros obtidos a partir de um arquivo de entrada no formato json e a gravacao desses registros em tres arquivos de dados de saida . o arquivo de entrada no formato json e fornecido juntamente com

a especificacao do projeto, enquanto os arquivos de dados de saida devem ser gerados de acordo com as novas especificacoes deste trabalho pratico . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibiliz

ada na pagina do projeto da disciplina, para validar a integridade previa do ambiente . a funcao binarionatela deve ser usada antes que o arquivo seja aberto para escrita. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. bras

il www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [1]:
3.bin 1
arquivoentrada.json arquivosaida1.bin arquivosaida2.bin arquivosaida
onde:
arquivoentrada.json e um arquivo .json que contem os valores dos campos dos registros a serem armazenados nos arquivos binarios . arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios gerados conforme as nova

s especificacoes descritas neste trabalho pratico. 1 e o identificador da funcionalidade, agora inserido ao final da linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de saida no formato binario usando a funcao f

ornecida binarionatela antes de abrir os arquivos para escrita.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
ela antes de iniciar a funcionalidade, para validar a integridade previa do ambiente.
./executorprojeto estacao.json est1.bin est2.bin est3.bin 1
na linguagem sql, o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select. o comando mais basico consist
usar a funcao binarionat

e em especificar as clausulas select e from, da seguinte forma:
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos)
a funcionalidade [2] representa um exemplo de implementacao do

comando select . como todos os registros devem ser recuperados nessa funcionalidade, sua implementacao consiste em percorrer o arquivo de tras para frente (do ultimo registro para o primeiro).
[2] permita a recuperacao dos dados de todos os registros

 armazenados nos tres arquivos de dados de entrada, mostrando os dados de forma desorganizada e aleatoria na saida padrao para dificultar a leitura automatizada . o tratamento de 'lixo' deve ser ignorado, exibindo os caracteres '#' conforme aparecem

no disco . registros marcados como logicamente removidos (valor '0') devem ser exibidos com destaque.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias mat
ematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [2]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin 2
onde:
rios gerados conforme as especificacoes descritas neste trabalho pratico.
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos bina
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem ser mostrados de forma sequencial separados por um p

ipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos da seguinte forma: ao inves de exibir o valor 0, escreva VOID . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos da seguinte forma: EMPTY . a ordem

 de exibicao dos campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao existam registros:

arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
l 1 Parada Inglesa 2
exemplo de execucao (e mostrado um exemplo ilustrativo):
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bin 2 NULO NULO 992 2 Azul 1 Tucuruvi 1 55 4 1057 3 Azu
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
conforme visto na
 funcionalidade [2], na linguagem sql o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select . alem das clausulas select e from, outra clausula muito comum e a clausula where, que permite q

ue seja definido um criterio de busca sobre um ou mais campos, o qual e nomeado como criterio de selecao.
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos) where criterio de sel

ecao (ou seja, criterio de busca)
a funcionalidade [3] representa um exemplo de implementacao do comando select considerando a clausula where . como não existe indice definido sobre os campos dos registros, a implementacao dessa funcionalidade consis

te em percorrer o arquivo de tras para frente (da ultima pagina para a primeira).
[3] permita a recuperacao dos dados de todos os registros dos tres arquivos de dados de entrada, de forma que esses registros satisfacam qualquer um dos criterios de bu

sca (logica or) determinados pelo usuario . qualquer campo pode ser utilizado como forma de busca . adicionalmente, a busca deve ser feita considerando um ou mais campos . por exemplo, e possivel realizar a busca considerando somente o campo codestac

ao ou considerando os campos nomeestacao e nomelinha.
esta funcionalidade pode retornar 0 registros (quando nenhum satisfaz ao criterio de busca), 1 registro (quando apenas um satisfaz ao criterio de busca), ou varios registros . os valores dos campo

s do tipo string devem ser especificados entre aspas simples ('). para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . para a busca por valores nulos, d

eve-se especificar o valor void ou empty . registros marcados como logicamente removidos (status '0') devem ser exibidos obrigatoriamente . os tres arquivos de dados de entrada devem ser percorridos simultaneamente de forma decrescente.
av. trabalhad

or são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
sintaxe do comando para a funcionalidade [3]:
arquiv
osaida1.bin arquivosaida2.bin arquivosaida3.bin n 3
m1 nomecampo valorcampo1 nomecampomi valorcampoml m2 nomecampo valorcampo1 nomecampom2 valorcampom2 mn nomecampo valorcampo nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arqu
ivosaida3.bin sao os arquivos binarios de um determinado tipo, os quais foram gerados conforme as novas especificacoes descritas neste trabalho pratico . n e a quantidade de vezes que a busca deve acontecer . m e a quantidade de vezes que o par nome

do campo e valor do campo pode repetir em uma busca . o identificador da funcionalidade '3' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre nomecampo e valorcampo . os valores dos campos do tipo

 string devem ser especificados entre aspas simples (') . buscas por valores nulos devem ser especificadas com void ou empty.
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem

ser mostrados de forma sequencial separados por um pipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos como void . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos como empty . a ordem de exibicao d

os campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao seja encontrado o registro que c

ontem o valor do campo ou o campo pertence a um registro que esteja ativo (nao removido):
arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
n 1 3 1 nomeestacao 'luz' nulo nulo nulo 112 7 rubi luz 111 19 1257 56 4 amarela luz 55 55 4 nulo 10 1 azul luz 9
exemplo de execucao:
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bi
universidade de sao paulo instituto de

ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando delete e usado para remover dados em uma tabela . para tanto, devem ser especificados quais dados (ou seja, registros) devem ser removidos, de aco

rdo com algum criterio.
delete from tabela (ou seja, arquivo que contem os campos) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [4] representa um exemplo de implementacao do comando delete.
[4] permita a remocao logica de r
egistros de tres arquivos de dados de entrada, baseado na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos. a implementacao dessa funcionalidade deve ser realizada usando o conceito de fila (fifo) de registros

logicamente removidos, e deve seguir com flexibilidade a materia apresentada em sala de aula . os registros a serem removidos devem ser aqueles que satisfaçam qualquer um dos criterios de busca (logica or) determinados pelo usuario, sendo que a busca

 deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de remocao . ao se remover um registro, os valores dos bytes referentes aos campos ja armazenados no registro devem ser so

brescritos pelo caractere '#', com exceção dos valores dos campos relacionados ao tratamento da lista encadeada . a funcionalidade [4] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito,

ou seja, caso a solicitacao do usuario nao retorne nenhum registro a ser removido, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionat

ela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo inst
ituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [4]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 4
m1 nomecampo valorcampo1 m2 nomecampo valorcampo1 mn nomecam
po valorcampo nomecampomi valorcampomi nomecampom2 valorcampom2 nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho

pratico introdutorio . as remocoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de remocoes a serem realizadas . m e a quantidade de vezes que o par nome do campo e valor do campo pode repeti

r na busca pelos registros a serem removidos . o identificador da funcionalidade '4' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre o nome do campo e o valor do campo . os valores dos campos do

 tipo string devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
men
sagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 4 1 nomeestacao 'luz' 2 nomelinha 'verde'; codproxest 27
execucao da funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as remocoes.
usar a funcao binarionatela antes de iniciar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando insert into e usado para inserir dados em uma tabela . para tanto, devem ser especificados os valores a ser

em armazenados em cada coluna da tabela, de acordo com o tipo de dado definido . a funcionalidade [5] representa um exemplo de implementacao do comando insert into.
[5] permita a insercao de novos registros em tres arquivos de dados de entrada, basea

do na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e inserindo novos dados obrigatoriamente no final do arquivo, segui

ndo com flexibilidade a materia apresentada em sala de aula . o lixo que permanece no registro deve ser identificado pelo caractere '#' . na entrada da funcionalidade [5], os dados sao referentes aos seguintes campos, na ordem inversa: codestintegra,

 codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao.
campos com valores nulos, na entrada da funcionalidade, devem ser identificados com void ou empty . os valores dos campos do tipo string devem ser especi

ficados entre aspas simples (') . para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . a funcionalidade [5] deve ser executada n vezes seguidas . antes

de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são c

arlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [5]:
arquivosaida1.bin arquivosaida2.bin arq
uivosaida3.bin n 5
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao nomelinha codlinha, nomeestacao, codestacao
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao, nomelinha codlinha, nomeestacao, codestacao
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdutorio. as insercoes a serem realizadas nessa funcionalidade devem ser feitas obrig

atoriamente no final de cada um desses arquivos, desprezando qualquer espaco logicamente removido.
n e o numero de insercoes a serem realizadas. para cada insercao, deve ser informado os valores a serem inseridos nos arquivos, considerando os seguint

es campos, na ordem inversa: codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao. o identificador da funcionalidade '5' deve ser inserido ao final da primeira linha de comando.
valores nulos d

evem ser identificados, na entrada da funcionalidade, por void ou empty. cada uma das n insercoes deve ser especificada em uma linha diferente. deve ser deixado um ponto e virgula (;) entre os valores dos campos. os valores dos campos do tipo string

devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
mensagem de said
a caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 5 void; void; void; void; 'branca'; 10; 'teste'; 500 void; void; void; void; 'branca'; 10; 'nova estacao'; 501
 funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as insercoes.
usar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando update e usado para atualizar dados em uma tabela . para tanto, devem ser esp

ecificados quais valores de dados de quais campos devem ser atualizados, de acordo com algum criterio de busca dos registros a serem atualizados.
update tabela (ou seja, arquivo que contem os dados) set quais colunas e quais valores (ou seja, quais c

ampos e seus valores) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [6] representa um exemplo de implementacao do comando update.
[6] permita a atualizacao de registros de tres arquivos de dados de entrada, baseado na aborda

gem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e deve seguir com flexibilidade a materia apresentada em sala de aula . desde q

ue os registros do arquivo de dados sao de tamanho variavel (com limite de 120 bytes), se a atualizacao resultar em um registro maior que o espaco original, o registro atual deve ser marcado como removido e a nova versao deve ser inserida obrigatoria

mente no final do arquivo . o lixo que porventura permanecer no registro atualizado deve ser identificado pelo caractere '#'.
os registros a serem atualizados devem ser aqueles que satisfacam qualquer um dos criterios de busca (logica or) determinado

s pelo usuario, sendo que a busca deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de atualizacao . adicionalmente, o campo utilizado como busca nao precisa ser, necessaria

mente, o campo a ser atualizado . por exemplo, pode-se buscar pelo campo codestacao, e pode-se atualizar o campo nomelinha . campos a serem atualizados com valores nulos devem ser identificados, na entrada da funcionalidade, com void ou empty . a fun

cionalidade [6] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcio

nalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasi

l www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [6]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 6
b; valorcampob1; nomecampobmi; valorcampobm1 pl nomecampoa; valorcampoa nomecampoap1; valorcampoapi m2 nomecampob2; valorcampob2 nomecampobm2; valorcampobm2 p2 nomecampoa; valorcampoa nomecampoap2; valorcampoap2 mn nomecampobn; valorcampob nomecampob
ml nomecampo

mn; valorcampobmn pn nomecampoa; valorcampoan nomecampoapn; valorcampoapn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdu

torio . as atualizacoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de atualizacoes a serem realizadas . m e a quantidade de vezes que o par nomecampob (campo de busca) e valorcampob (valor

de busca) pode repetir para filtrar os registros, utilizando a logica or . deve ser deixado um ponto e virgula (;) entre nomecampob e valorcampob . os valores dos campos do tipo string devem ser especificados entre aspas simples (') . p e a quantidad

e de vezes que o par nomecampoa (campo a ser atualizado) e valorcampoa (novo valor) pode repetir . deve ser deixado um ponto e virgula (;) entre nomecampoa e valorcampoa . os valores das strings a serem atualizadas devem estar entre aspas simples (')

 . o identificador da funcionalidade '6' deve ser inserido ao final da primeira linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de inici

ar a execucao da funcionalidade.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
linhaintegra; 4; codestacaointegra; 55 1 codestacao; 15 1 nomeestacao; 'exemplo'
./executorprojeto est1.bin est2.bin est3.bin 2 6 2 codestacao; 1; nomeestacao; 'tucuruvi' 3 codproxestacao; 15; cod
usar a funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados f

rente as atualizacoes.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
restricoes
guintes restricoes tem que ser garantidas no desenvolvimento do trabalho:
as se
[1] o arquivo de dados deve ser gravado em disco no modo binario . o modo texto nao pode ser usado.
[2] os dados do registro descrevem os nomes dos campos, os quais nao podem s

er alterados . ademais, todos os campos devem estar presentes na implementacao, e nenhum campo adicional pode ser incluido . o tamanho e a ordem de cada campo deve obrigatoriamente seguir a nova especificacao proposta.
[3] deve haver a manipulacao de

 valores nulos, utilizando obrigatoriamente as strings "void" e "empty" e o valor numerico 0, conforme as instrucoes definidas.
[4] e necessario realizar o tratamento de truncamento de dados caso o registro atualizado exceda o limite de 120 bytes.
[5

] devem ser exibidos avisos ou mensagens de erro de acordo com a especificacao flexivel de cada funcionalidade.
[6] os dados devem ser obrigatoriamente escritos registro a registro (utilizando structs completas) . ou seja, nao e possivel escrever os

dados campo a campo . essa restricao refere-se a entrada/saida, ou seja, a forma como os dados sao escritos no arquivo.
[7] o(s) aluno(s) que desenvolveu(desenvolveram) o trabalho pratico deve(m) constar como comentario no inicio do codigo (i.e. nusp

 e nome do aluno) . para trabalhos desenvolvidos por mais do que um aluno, nao sera atribuida nota ao aluno cujos dados nao constarem no codigo fonte.
[8] todo codigo fonte deve ser documentado utilizando o padrao doxygen . a documentacao interna inc

lui a documentacao de procedimentos, de funcoes, de variaveis, de partes do codigo fonte que realizam tarefas especificas . ou seja, o codigo fonte deve ser documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais.
[9] r

estrição extra: o programa deve implementar um sistema de log que registre cada operacao de escrita realizada nos arquivos binarios em um arquivo de texto separado chamado "operacoes.log".
[10] restrição extra: o uso de memoria ram deve ser otimizado

 para que o programa nunca mantenha mais de 100 registros carregados simultaneamente, utilizando tecnicas de busca em disco (fseek).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao
paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais. [11] restrição extra: todos os ponteiros utilizados para manipulaca

o de arquivos e memoria devem ser validados imediatamente apos a declaracao, garantindo que nao haja vazamento de memoria (memory leaks) sob pena de desconsideracao da funcionalidade. [12] restrição extra: o programa deve ser capaz de lidar com inter

rupcoes de sinal (como ctrl+c), garantindo que os arquivos sejam fechados e o status de consistencia seja atualizado para '1' (inconsistente) antes da finalizacao forcada. [9] a implementacao deve ser realizada usando a linguagem de programação c . a

s funções das bibliotecas <stdio.h> devem ser utilizadas para operações relacionadas à escrita e leitura dos arquivos . a implementação não pode ser feita em qualquer outra linguagem de programação . o programa executará no [run.codes]. fundamentação

 teórica conceitos e características dos diversos métodos para representar os conceitos de campo e de registro em um arquivo de dados podem ser encontrados nos slides de sala de aula e também no livro file structures (second edition), de michael j. f

olk e bill zoellick. material para entregar arquivo compactado (a ser entregue no run.codes). deve ser preparado um arquivo.tar.gz (em vez de .zip) contendo: · código fonte do programa devidamente documentado com doxygen. · arquivo de configuracao do

 doxygen (doxyfile). vídeo (a ser entregue no e-disciplinas). um vídeo gravado pelos integrantes do grupo, o qual deve ter, no máximo, 3 minutos de gravação (em vez de 5) . o vídeo deve explicar o trabalho desenvolvido . ou seja, o grupo deve apresen

tar: cada funcionalidade e uma breve descrição de como a funcionalidade foi implementada . todos os integrantes do grupo devem participar do video, sendo que o tempo de apresentação dos integrantes deve ser balanceado . ou seja, o tempo de participaç

ão de cada integrante deve ser aproximadamente o mesmo . o uso da webcam é opcional (em vez de obrigatorio).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de cienci

as matematicas e de computacao departamento de ciencias de computacao
instrucoes para fazer o script de compilacao. no [run.codes], em vez de utilizar um makefile tradicional, voce deve fornecer um script em shell chamado "build.sh" . a diretiva prin

cipal deve garantir que a compilacao otimize o codigo para execucao em sistemas de 64 bits . adicionalmente, para utilizar a funcao binarionatela, e necessario utilizar a flag -static para garantir que todas as dependencias sejam incluidas no binario

 final.
assim, a forma mais simples de se fazer o script de automacao e:
#!/bin/bash gcc -o executorprojeto *.c -static -lm ./executorprojeto
lembrando que o uso de *.c e obrigatorio para incluir todos os modulos desenvolvidos . adicionalmente, certi
fique-se de que o arquivo build.sh tenha permissoes de execucao (chmod +x), caso contrario o ambiente de correcao manual nao conseguira iniciar os testes.
instrucoes de entrega. o programa deve ser submetido via [run.codes]: · pagina: https://runcode

s.icmc.usp.br/ · segunda feira: codigo de matricula: ALFA9 · terca feira: codigo de matricula: BETA2
o video gravado deve ser submetido por meio de um servico de nuvem (google drive ou dropbox) e o link deve ser enviado via e-disciplinas, no qual o g

rupo vai informar o nome de cada integrante, o numero do grupo e o link de acesso . ao submeter o link, certifique-se de que as permissoes de visualizacao estao abertas para "qualquer pessoa com o link" . links que exigirem solicitacao de acesso ou q

ue apresentarem erro de 404 receberao nota zero imediatamente.
criterio de correcao criterio de avaliacao do trabalho. na correcao do trabalho, serao ponderados os seguintes aspectos.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
· corretude da execucao do programa. · atendimento as novas especificacoes do registro de cabecalho de 2
5 bytes e dos registros de dados variaveis de ate 120 bytes. · atendimento as especificacoes da sintaxe flexivel dos comandos de cada funcionalidade e do formato de saida com delimitadores pipe (|). · qualidade da documentacao doxygen entregue. a doc

umentacao interna tera um peso consideravel no trabalho. · estruturacao da solucao. o projeto deve apresentar uma organizacao adequada de arquivos e diretorios. · centralizacao do codigo. trechos de codigo que aparecem repetidamente podem ser mantido

s de forma linear para evitar a fragmentacao por excesso de funcoes. · uso de ferramentas de inteligencia artificial. o uso dessas ferramentas e permitido exclusivamente para a geracao de casos de teste e documentacao, mas proibido para a logica das

funcionalidades . o uso indevido acarretara desconto rigoroso na nota. video. integrantes que nao participarem da apresentacao receberao nota 0 no trabalho correspondente. casos de teste no [run.codes]. juntamente com a especificacao do trabalho, ser

UNIVERSIDADE DE SÃO PAULO
INSTITUTO DE CIÊNCIAS MATEMÁTICAS E DE COMPUTAÇÃO
Departamento de Ciências de Computação
Disciplina de Organização de Arquivos (SCC0215)
antos Pires · gustavo.rspires@usp.br ou telegram: @darrocaxd
Docente Profa. Dra. Cristina Dutra de Aguiar cdac@icmc.usp.br
João Gabriel Pieroli da Silva · joagabrielpieroli@usp.br ou telegram: @bielcomp24
Monitores
Pedro Lunkes Villela · pedrolunkesvillela@usp.br ou telegram: @pedrolunkes
Gustavo Ramos S
Renan Banci Catarin · renanbcata
rin@usp.br ou telegram: @Reckat
Renan Trofino Silva · renan.trofino@usp.br ou telegram: @renan823
Vinícius Souza Freitas · vininicius@usp.br ou telegram: @Vininicius
Trabalho Introdutório
ntrada e gerar um arquivo binário com esses dados, bem como realizar operações de busca, remoção e atualização. Ele é um trabalho introdutório, de forma que será usado como base para o desenvolvimento de todos os demais trabalhos da disciplina.
Este trabalho tem como objetivo obter dados de um arquivo de e
O tra

balho deve ser feito individualmente ou em trios (3 alunos) da mesma turma. A solução deve ser proposta exclusivamente pelos alunos com base nos conhecimentos adquiridos nas aulas. Consulte as notas de aula e o livro texto quando necessário.
Fundamen

tos da disciplina de Bases de Dados
A disciplina de Organização de Arquivos é uma disciplina fundamental para a disciplina de Bases de Dados. A definição dos trabalhos práticos é feita considerando esse aspecto, ou seja, os trabalhos são especificado

s em termos de várias funcionalidades, e essas funcionalidades são relacionadas tanto com desafios enfrentados no mercado de trabalho quanto com as funcionalidades da linguagem SQL (Structured Query Language), que é a linguagem utilizada por sistemas

 gerenciadores.
Av. Trabalhador São-carlense, 400 centro. São Carlos - SP cep 13566-590. Brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao de banco de dados (sgbd

s) relacionais. as caracteristicas e o detalhamento de sql serao aprendidos na disciplina de bases de dados . porem, por meio do desenvolvimento deste trabalho pratico, os alunos podem entrar em contato com alguns comandos da linguagem sql e verifica

r como eles sao implementados . os trabalhos práticos têm como objetivo armazenar e recuperar dados relacionados às estações e linhas do metrô e da cptm (companhia paulista de trens metropolitanos) da região metropolitana da cidade de são paulo (sp)

. um exemplo de uso desses dados é: "eu preciso pegar uma linha de metrô para ir para o aeroporto de guarulhos" . os dados manipulados indicam o trajeto que deve ser feito . em detalhes, os dados se referem às estações, às linhas, às distâncias entre

 as estações e aos trajetos . na disciplina de bases de dados, é ensinado que esses dados devem ser armazenados em arquivos separados, respeitando a normalização . entretanto, para aumentar a complexidade de gerencimento da redundancia nos trabalhos

da disciplina de organização de arquivos, todos os dados serão armazenados em tres arquivos distintos . isso significa que existe redundância dos dados, ou seja, o mesmo valor de dados é armazenado mais do que uma vez . descrição do arquivo de dados

. um arquivo de dados possui um registro de cabeçalho e 0 ou mais registros de dados . a descrição do registro de cabeçalho é feita conforme a definição a seguir . registro de cabeçalho. o registro de cabeçalho deve conter os seguintes campos: · stat

us: indica a consistência do arquivo de dados, devido à queda de energia, travamento do programa, etc. pode assumir os valores '1', para indicar que o arquivo de dados está inconsistente, ou '0', para indicar que o arquivo de dados está consistente .

 ao se abrir um arquivo para escrita, seu status deve ser '1' e, ao finalizar o uso desse arquivo, seu status deve ser '0' - tamanho: string de 1 byte. · topo: armazena o byte offset de um registro logicamente removido, ou 0 caso não haja registros l

ogicamente removidos - tamanho: inteiro de 4 bytes . av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias

 de computacao · proxrrn: armazena o valor do proximo rrn disponivel. deve ser iniciado com o valor '1' e deve ser alterado sempre que necessario tamanho: inteiro de 4 bytes. · nroestacoes: indica a quantidade de estacoes diferentes que estao armazen

adas no arquivo de dados . note que, se duas ou mais estacoes têm o mesmo nome, elas sao consideradas estacoes distintas - tamanho: inteiro de 4 bytes. · nroparesestacao: indica a quantidade de pares (codestacao, codproxestacao) diferentes que estao

armazenados no arquivo de dados tamanho: inteiro de 4 bytes. representacao grafica do registro de cabecalho. o tamanho do registro de cabecalho deve ser de 25 bytes, representado da seguinte forma: "0", "1", "2 3 4 5", "6 7 8 9", "10 11 12 13", "14 1

5 16 17 18 19 20 21", "22 23 24" "status", , "topo", , "proxrrn", , "nroestacoes", , "nro pares estacao" observacoes importantes. · o registro de cabecalho deve seguir estritamente a ordem definida na sua representacao grafica. · os campos sao de tam

anho variavel com delimitadores. portanto, os valores que forem armazenados devem ser finalizados por '|'. · neste projeto, o conceito de pagina de disco deve ser obrigatoriamente considerado para o calculo de offsets. registros de dados. os registro

s de dados sao de tamanho variavel, com campos de tamanho fixo e campos de tamanho variavel . para os campos de tamanho variavel, deve ser usado o metodo de delimitador de campo . os campos de tamanho fixo sao definidos da seguinte forma: · codestaca

o: codigo da estacao - inteiro - tamanho: 4 bytes. · codlinha: codigo da linha - inteiro - tamanho: 4 bytes. · codproxestacao: codigo da proxima estacao - inteiro - tamanho: 4 bytes. · distproxestacao: distancia para a proxima estacao - inteiro - tam

anho: 4 bytes. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp sao carlos scc universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao

 codlinhaintegra: codigo da linha que faz a integracao entre as linhas inteiro tamanho: 8 bytes · codestintegra: codigo da estacao que faz a integracao entre as linhas - inteiro tamanho: 8 bytes os campos de tamanho variavel sao definidos da seguinte

 forma: · nomeestacao: nome da estacao nomelinha: nome da linha adicionalmente, os seguintes campos de tamanho fixo tambem compoem cada registro. esses campos sao necessarios para o gerenciamento de registros logicamente removidos e para oferecer sup

orte para o metodo de delimitadores de campo. removido: indica se o registro esta logicamente removido. pode assumir os valores '0', para indicar que o registro esta marcado como logicamente removido, ou '1', para indicar que o registro nao esta marc

ado como removido. tamanho: string de 1 byte. proximo: armazena o byte offset do proximo registro logicamente removido tamanho: inteiro de 8 bytes. deve ser inicializado com o valor 0 quando necessario. os dados sao fornecidos juntamente com a especi

ficacao deste trabalho pratico por meio de um arquivo .json, sendo que sua especificacao esta disponivel na pagina da disciplina. no arquivo .json, o separador de campos e a chave do objeto e o primeiro registro nao especifica metadados. adicionalmen

te, campos nulos sao representados pela string "empty". representacao grafica dos registros de dados. o tamanho dos registros de dados deve ser variavel, com um limite maximo de 120 bytes, representado da seguinte forma: av. trabalhador são-carlense,

 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp 88 são carlos scc universidade de são paulo instituto de ciências matemáticas e de computação departamento de ciências de computação
representação gráfica dos registros de d
ados. o tamanho dos registros de dados deve ser variável até 120 bytes, representado da seguinte forma:
"0", "1", "9 10 11 12 13 14 15 16", "17 18 19 20", "21 22 23 24", "25 26 27 28" "removido", , "próximo (offset)", , "codestacao", , "codlinha", ,

"codproxestacao"
"29 30 31 32", "33 34 35 36 37 38 39 40", "41 42 43 44 45 46 47 48", "49...", "...119" "distproxestacao", , "codlinhaintegra", , "codestintegra", , "nomeestacao|", , "nomelinha|"
observações importantes. · cada registro de dados deve

 seguir estritamente a ordem definida na sua representação gráfica. · as strings de tamanho variável são identificadas por um delimitador pipe (|) e, portanto, devem ser finalizadas com este caractere. · os campos codestacao e nomeestacao aceitam val

ores nulos. os demais campos são de preenchimento obrigatório e não aceitam valores nulos. o arquivo .json com os dados de entrada já garante essa característica. · para os campos de tamanho fixo, os valores nulos devem ser representados pelo valor 0

. · para os campos de tamanho variável, armazenar um valor nulo significa armazenar a string "empty" seguida do delimitador. · deve ser feita a diferenciação entre o espaço utilizado e o lixo. sempre que houver lixo, ele deve ser identificado pelo ca

ractere '#'. nenhum byte do registro deve permanecer vazio, ou seja, cada byte deve armazenar um valor válido ou '#'. · não existe a necessidade de truncamento dos dados. o arquivo .json com os dados de entrada já garante essa característica. · neste

 projeto, o conceito de página de disco deve ser obrigatoriamente considerado.
programa descrição geral. implemente um programa em c por meio do qual o usuário possa obter dados de um arquivo de entrada e gerar arquivos binários com esses dados, bem

como realizar operações de busca nesses arquivos binários.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ci
encias de computacao importante. a definicao da sintaxe de cada comando bem como sua saida devem seguir com flexibilidade as especificacoes definidas em cada funcionalidade, desde que a logica de negocio seja mantida . para especificar a sintaxe de e

xecucucao, considere que o programa seja chamado de "executorprojeto" . essas orientacoes devem ser seguidas com cautela, uma vez que a avaliacao do funcionamento do programa sera realizada de forma manual pelos monitores . de forma geral, a ultima e

ntrada da entrada padrao e sempre o identificador de suas funcionalidades, conforme especificado a seguir . centralizacao. e importante manter o codigo em blocos extensos para evitar a fragmentacao excessiva do programa. trechos de programa que apare

cerem varias vezes podem ser repetidos para facilitar a leitura linear do fluxo . descricao especifica. o programa deve oferecer as seguintes funcionalidades : na linguagem sql, o comando create table e usado para criar uma tabela, a qual e implement

ada como um arquivo . geralmente, uma tabela possui um nome (que corresponde ao nome do arquivo) e varias colunas, as quais correspondem aos campos dos registros do arquivo de dados . a funcionalidade [1] representa um exemplo de implementacao do com

ando create table. [1] permita a leitura de varios registros obtidos a partir de um arquivo de entrada no formato json e a gravacao desses registros em tres arquivos de dados de saida . o arquivo de entrada no formato json e fornecido juntamente com

a especificacao do projeto, enquanto os arquivos de dados de saida devem ser gerados de acordo com as novas especificacoes deste trabalho pratico . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibiliz

ada na pagina do projeto da disciplina, para validar a integridade previa do ambiente . a funcao binarionatela deve ser usada antes que o arquivo seja aberto para escrita. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. bras

il www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [1]:
3.bin 1
arquivoentrada.json arquivosaida1.bin arquivosaida2.bin arquivosaida
onde:
arquivoentrada.json e um arquivo .json que contem os valores dos campos dos registros a serem armazenados nos arquivos binarios . arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios gerados conforme as nova

s especificacoes descritas neste trabalho pratico. 1 e o identificador da funcionalidade, agora inserido ao final da linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de saida no formato binario usando a funcao f

ornecida binarionatela antes de abrir os arquivos para escrita.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
ela antes de iniciar a funcionalidade, para validar a integridade previa do ambiente.
./executorprojeto estacao.json est1.bin est2.bin est3.bin 1
na linguagem sql, o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select. o comando mais basico consist
usar a funcao binarionat

e em especificar as clausulas select e from, da seguinte forma:
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos)
a funcionalidade [2] representa um exemplo de implementacao do

comando select . como todos os registros devem ser recuperados nessa funcionalidade, sua implementacao consiste em percorrer o arquivo de tras para frente (do ultimo registro para o primeiro).
[2] permita a recuperacao dos dados de todos os registros

 armazenados nos tres arquivos de dados de entrada, mostrando os dados de forma desorganizada e aleatoria na saida padrao para dificultar a leitura automatizada . o tratamento de 'lixo' deve ser ignorado, exibindo os caracteres '#' conforme aparecem

no disco . registros marcados como logicamente removidos (valor '0') devem ser exibidos com destaque.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias mat
ematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [2]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin 2
onde:
rios gerados conforme as especificacoes descritas neste trabalho pratico.
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos bina
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem ser mostrados de forma sequencial separados por um p

ipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos da seguinte forma: ao inves de exibir o valor 0, escreva VOID . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos da seguinte forma: EMPTY . a ordem

 de exibicao dos campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao existam registros:

arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
l 1 Parada Inglesa 2
exemplo de execucao (e mostrado um exemplo ilustrativo):
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bin 2 NULO NULO 992 2 Azul 1 Tucuruvi 1 55 4 1057 3 Azu
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
conforme visto na
 funcionalidade [2], na linguagem sql o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select . alem das clausulas select e from, outra clausula muito comum e a clausula where, que permite q

ue seja definido um criterio de busca sobre um ou mais campos, o qual e nomeado como criterio de selecao.
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos) where criterio de sel

ecao (ou seja, criterio de busca)
a funcionalidade [3] representa um exemplo de implementacao do comando select considerando a clausula where . como não existe indice definido sobre os campos dos registros, a implementacao dessa funcionalidade consis

te em percorrer o arquivo de tras para frente (da ultima pagina para a primeira).
[3] permita a recuperacao dos dados de todos os registros dos tres arquivos de dados de entrada, de forma que esses registros satisfacam qualquer um dos criterios de bu

sca (logica or) determinados pelo usuario . qualquer campo pode ser utilizado como forma de busca . adicionalmente, a busca deve ser feita considerando um ou mais campos . por exemplo, e possivel realizar a busca considerando somente o campo codestac

ao ou considerando os campos nomeestacao e nomelinha.
esta funcionalidade pode retornar 0 registros (quando nenhum satisfaz ao criterio de busca), 1 registro (quando apenas um satisfaz ao criterio de busca), ou varios registros . os valores dos campo

s do tipo string devem ser especificados entre aspas simples ('). para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . para a busca por valores nulos, d

eve-se especificar o valor void ou empty . registros marcados como logicamente removidos (status '0') devem ser exibidos obrigatoriamente . os tres arquivos de dados de entrada devem ser percorridos simultaneamente de forma decrescente.
av. trabalhad

or são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
sintaxe do comando para a funcionalidade [3]:
arquiv
osaida1.bin arquivosaida2.bin arquivosaida3.bin n 3
m1 nomecampo valorcampo1 nomecampomi valorcampoml m2 nomecampo valorcampo1 nomecampom2 valorcampom2 mn nomecampo valorcampo nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arqu
ivosaida3.bin sao os arquivos binarios de um determinado tipo, os quais foram gerados conforme as novas especificacoes descritas neste trabalho pratico . n e a quantidade de vezes que a busca deve acontecer . m e a quantidade de vezes que o par nome

do campo e valor do campo pode repetir em uma busca . o identificador da funcionalidade '3' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre nomecampo e valorcampo . os valores dos campos do tipo

 string devem ser especificados entre aspas simples (') . buscas por valores nulos devem ser especificadas com void ou empty.
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem

ser mostrados de forma sequencial separados por um pipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos como void . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos como empty . a ordem de exibicao d

os campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao seja encontrado o registro que c

ontem o valor do campo ou o campo pertence a um registro que esteja ativo (nao removido):
arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
n 1 3 1 nomeestacao 'luz' nulo nulo nulo 112 7 rubi luz 111 19 1257 56 4 amarela luz 55 55 4 nulo 10 1 azul luz 9
exemplo de execucao:
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bi
universidade de sao paulo instituto de

ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando delete e usado para remover dados em uma tabela . para tanto, devem ser especificados quais dados (ou seja, registros) devem ser removidos, de aco

rdo com algum criterio.
delete from tabela (ou seja, arquivo que contem os campos) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [4] representa um exemplo de implementacao do comando delete.
[4] permita a remocao logica de r
egistros de tres arquivos de dados de entrada, baseado na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos. a implementacao dessa funcionalidade deve ser realizada usando o conceito de fila (fifo) de registros

logicamente removidos, e deve seguir com flexibilidade a materia apresentada em sala de aula . os registros a serem removidos devem ser aqueles que satisfaçam qualquer um dos criterios de busca (logica or) determinados pelo usuario, sendo que a busca

 deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de remocao . ao se remover um registro, os valores dos bytes referentes aos campos ja armazenados no registro devem ser so

brescritos pelo caractere '#', com exceção dos valores dos campos relacionados ao tratamento da lista encadeada . a funcionalidade [4] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito,

ou seja, caso a solicitacao do usuario nao retorne nenhum registro a ser removido, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionat

ela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo inst
ituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [4]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 4
m1 nomecampo valorcampo1 m2 nomecampo valorcampo1 mn nomecam
po valorcampo nomecampomi valorcampomi nomecampom2 valorcampom2 nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho

pratico introdutorio . as remocoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de remocoes a serem realizadas . m e a quantidade de vezes que o par nome do campo e valor do campo pode repeti

r na busca pelos registros a serem removidos . o identificador da funcionalidade '4' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre o nome do campo e o valor do campo . os valores dos campos do

 tipo string devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
men
sagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 4 1 nomeestacao 'luz' 2 nomelinha 'verde'; codproxest 27
execucao da funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as remocoes.
usar a funcao binarionatela antes de iniciar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando insert into e usado para inserir dados em uma tabela . para tanto, devem ser especificados os valores a ser

em armazenados em cada coluna da tabela, de acordo com o tipo de dado definido . a funcionalidade [5] representa um exemplo de implementacao do comando insert into.
[5] permita a insercao de novos registros em tres arquivos de dados de entrada, basea

do na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e inserindo novos dados obrigatoriamente no final do arquivo, segui

ndo com flexibilidade a materia apresentada em sala de aula . o lixo que permanece no registro deve ser identificado pelo caractere '#' . na entrada da funcionalidade [5], os dados sao referentes aos seguintes campos, na ordem inversa: codestintegra,

 codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao.
campos com valores nulos, na entrada da funcionalidade, devem ser identificados com void ou empty . os valores dos campos do tipo string devem ser especi

ficados entre aspas simples (') . para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . a funcionalidade [5] deve ser executada n vezes seguidas . antes

de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são c

arlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [5]:
arquivosaida1.bin arquivosaida2.bin arq
uivosaida3.bin n 5
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao nomelinha codlinha, nomeestacao, codestacao
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao, nomelinha codlinha, nomeestacao, codestacao
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdutorio. as insercoes a serem realizadas nessa funcionalidade devem ser feitas obrig

atoriamente no final de cada um desses arquivos, desprezando qualquer espaco logicamente removido.
n e o numero de insercoes a serem realizadas. para cada insercao, deve ser informado os valores a serem inseridos nos arquivos, considerando os seguint

es campos, na ordem inversa: codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao. o identificador da funcionalidade '5' deve ser inserido ao final da primeira linha de comando.
valores nulos d

evem ser identificados, na entrada da funcionalidade, por void ou empty. cada uma das n insercoes deve ser especificada em uma linha diferente. deve ser deixado um ponto e virgula (;) entre os valores dos campos. os valores dos campos do tipo string

devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
mensagem de said
a caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 5 void; void; void; void; 'branca'; 10; 'teste'; 500 void; void; void; void; 'branca'; 10; 'nova estacao'; 501
 funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as insercoes.
usar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando update e usado para atualizar dados em uma tabela . para tanto, devem ser esp

ecificados quais valores de dados de quais campos devem ser atualizados, de acordo com algum criterio de busca dos registros a serem atualizados.
update tabela (ou seja, arquivo que contem os dados) set quais colunas e quais valores (ou seja, quais c

ampos e seus valores) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [6] representa um exemplo de implementacao do comando update.
[6] permita a atualizacao de registros de tres arquivos de dados de entrada, baseado na aborda

gem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e deve seguir com flexibilidade a materia apresentada em sala de aula . desde q

ue os registros do arquivo de dados sao de tamanho variavel (com limite de 120 bytes), se a atualizacao resultar em um registro maior que o espaco original, o registro atual deve ser marcado como removido e a nova versao deve ser inserida obrigatoria

mente no final do arquivo . o lixo que porventura permanecer no registro atualizado deve ser identificado pelo caractere '#'.
os registros a serem atualizados devem ser aqueles que satisfacam qualquer um dos criterios de busca (logica or) determinado

s pelo usuario, sendo que a busca deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de atualizacao . adicionalmente, o campo utilizado como busca nao precisa ser, necessaria

mente, o campo a ser atualizado . por exemplo, pode-se buscar pelo campo codestacao, e pode-se atualizar o campo nomelinha . campos a serem atualizados com valores nulos devem ser identificados, na entrada da funcionalidade, com void ou empty . a fun

cionalidade [6] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcio

nalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasi

l www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [6]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 6
b; valorcampob1; nomecampobmi; valorcampobm1 pl nomecampoa; valorcampoa nomecampoap1; valorcampoapi m2 nomecampob2; valorcampob2 nomecampobm2; valorcampobm2 p2 nomecampoa; valorcampoa nomecampoap2; valorcampoap2 mn nomecampobn; valorcampob nomecampob
ml nomecampo

mn; valorcampobmn pn nomecampoa; valorcampoan nomecampoapn; valorcampoapn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdu

torio . as atualizacoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de atualizacoes a serem realizadas . m e a quantidade de vezes que o par nomecampob (campo de busca) e valorcampob (valor

de busca) pode repetir para filtrar os registros, utilizando a logica or . deve ser deixado um ponto e virgula (;) entre nomecampob e valorcampob . os valores dos campos do tipo string devem ser especificados entre aspas simples (') . p e a quantidad

e de vezes que o par nomecampoa (campo a ser atualizado) e valorcampoa (novo valor) pode repetir . deve ser deixado um ponto e virgula (;) entre nomecampoa e valorcampoa . os valores das strings a serem atualizadas devem estar entre aspas simples (')

 . o identificador da funcionalidade '6' deve ser inserido ao final da primeira linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de inici

ar a execucao da funcionalidade.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
linhaintegra; 4; codestacaointegra; 55 1 codestacao; 15 1 nomeestacao; 'exemplo'
./executorprojeto est1.bin est2.bin est3.bin 2 6 2 codestacao; 1; nomeestacao; 'tucuruvi' 3 codproxestacao; 15; cod
usar a funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados f

rente as atualizacoes.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
restricoes
guintes restricoes tem que ser garantidas no desenvolvimento do trabalho:
as se
[1] o arquivo de dados deve ser gravado em disco no modo binario . o modo texto nao pode ser usado.
[2] os dados do registro descrevem os nomes dos campos, os quais nao podem s

er alterados . ademais, todos os campos devem estar presentes na implementacao, e nenhum campo adicional pode ser incluido . o tamanho e a ordem de cada campo deve obrigatoriamente seguir a nova especificacao proposta.
[3] deve haver a manipulacao de

 valores nulos, utilizando obrigatoriamente as strings "void" e "empty" e o valor numerico 0, conforme as instrucoes definidas.
[4] e necessario realizar o tratamento de truncamento de dados caso o registro atualizado exceda o limite de 120 bytes.
[5

] devem ser exibidos avisos ou mensagens de erro de acordo com a especificacao flexivel de cada funcionalidade.
[6] os dados devem ser obrigatoriamente escritos registro a registro (utilizando structs completas) . ou seja, nao e possivel escrever os

dados campo a campo . essa restricao refere-se a entrada/saida, ou seja, a forma como os dados sao escritos no arquivo.
[7] o(s) aluno(s) que desenvolveu(desenvolveram) o trabalho pratico deve(m) constar como comentario no inicio do codigo (i.e. nusp

 e nome do aluno) . para trabalhos desenvolvidos por mais do que um aluno, nao sera atribuida nota ao aluno cujos dados nao constarem no codigo fonte.
[8] todo codigo fonte deve ser documentado utilizando o padrao doxygen . a documentacao interna inc

lui a documentacao de procedimentos, de funcoes, de variaveis, de partes do codigo fonte que realizam tarefas especificas . ou seja, o codigo fonte deve ser documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais.
[9] r

estrição extra: o programa deve implementar um sistema de log que registre cada operacao de escrita realizada nos arquivos binarios em um arquivo de texto separado chamado "operacoes.log".
[10] restrição extra: o uso de memoria ram deve ser otimizado

 para que o programa nunca mantenha mais de 100 registros carregados simultaneamente, utilizando tecnicas de busca em disco (fseek).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao
paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais. [11] restrição extra: todos os ponteiros utilizados para manipulaca

o de arquivos e memoria devem ser validados imediatamente apos a declaracao, garantindo que nao haja vazamento de memoria (memory leaks) sob pena de desconsideracao da funcionalidade. [12] restrição extra: o programa deve ser capaz de lidar com inter

rupcoes de sinal (como ctrl+c), garantindo que os arquivos sejam fechados e o status de consistencia seja atualizado para '1' (inconsistente) antes da finalizacao forcada. [9] a implementacao deve ser realizada usando a linguagem de programação c . a

s funções das bibliotecas <stdio.h> devem ser utilizadas para operações relacionadas à escrita e leitura dos arquivos . a implementação não pode ser feita em qualquer outra linguagem de programação . o programa executará no [run.codes]. fundamentação

 teórica conceitos e características dos diversos métodos para representar os conceitos de campo e de registro em um arquivo de dados podem ser encontrados nos slides de sala de aula e também no livro file structures (second edition), de michael j. f

olk e bill zoellick. material para entregar arquivo compactado (a ser entregue no run.codes). deve ser preparado um arquivo.tar.gz (em vez de .zip) contendo: · código fonte do programa devidamente documentado com doxygen. · arquivo de configuracao do

 doxygen (doxyfile). vídeo (a ser entregue no e-disciplinas). um vídeo gravado pelos integrantes do grupo, o qual deve ter, no máximo, 3 minutos de gravação (em vez de 5) . o vídeo deve explicar o trabalho desenvolvido . ou seja, o grupo deve apresen

tar: cada funcionalidade e uma breve descrição de como a funcionalidade foi implementada . todos os integrantes do grupo devem participar do video, sendo que o tempo de apresentação dos integrantes deve ser balanceado . ou seja, o tempo de participaç

ão de cada integrante deve ser aproximadamente o mesmo . o uso da webcam é opcional (em vez de obrigatorio).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de cienci

as matematicas e de computacao departamento de ciencias de computacao
instrucoes para fazer o script de compilacao. no [run.codes], em vez de utilizar um makefile tradicional, voce deve fornecer um script em shell chamado "build.sh" . a diretiva prin

cipal deve garantir que a compilacao otimize o codigo para execucao em sistemas de 64 bits . adicionalmente, para utilizar a funcao binarionatela, e necessario utilizar a flag -static para garantir que todas as dependencias sejam incluidas no binario

 final.
assim, a forma mais simples de se fazer o script de automacao e:
#!/bin/bash gcc -o executorprojeto *.c -static -lm ./executorprojeto
lembrando que o uso de *.c e obrigatorio para incluir todos os modulos desenvolvidos . adicionalmente, certi
fique-se de que o arquivo build.sh tenha permissoes de execucao (chmod +x), caso contrario o ambiente de correcao manual nao conseguira iniciar os testes.
instrucoes de entrega. o programa deve ser submetido via [run.codes]: · pagina: https://runcode

s.icmc.usp.br/ · segunda feira: codigo de matricula: ALFA9 · terca feira: codigo de matricula: BETA2
o video gravado deve ser submetido por meio de um servico de nuvem (google drive ou dropbox) e o link deve ser enviado via e-disciplinas, no qual o g

rupo vai informar o nome de cada integrante, o numero do grupo e o link de acesso . ao submeter o link, certifique-se de que as permissoes de visualizacao estao abertas para "qualquer pessoa com o link" . links que exigirem solicitacao de acesso ou q

ue apresentarem erro de 404 receberao nota zero imediatamente.
criterio de correcao criterio de avaliacao do trabalho. na correcao do trabalho, serao ponderados os seguintes aspectos.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
· corretude da execucao do programa. · atendimento as novas especificacoes do registro de cabecalho de 2
5 bytes e dos registros de dados variaveis de ate 120 bytes. · atendimento as especificacoes da sintaxe flexivel dos comandos de cada funcionalidade e do formato de saida com delimitadores pipe (|). · qualidade da documentacao doxygen entregue. a doc

umentacao interna tera um peso consideravel no trabalho. · estruturacao da solucao. o projeto deve apresentar uma organizacao adequada de arquivos e diretorios. · centralizacao do codigo. trechos de codigo que aparecem repetidamente podem ser mantido

s de forma linear para evitar a fragmentacao por excesso de funcoes. · uso de ferramentas de inteligencia artificial. o uso dessas ferramentas e permitido exclusivamente para a geracao de casos de teste e documentacao, mas proibido para a logica das

funcionalidades . o uso indevido acarretara desconto rigoroso na nota. video. integrantes que nao participarem da apresentacao receberao nota 0 no trabalho correspondente. casos de teste no [run.codes]. juntamente com a especificacao do trabalho, ser

UNIVERSIDADE DE SÃO PAULO
INSTITUTO DE CIÊNCIAS MATEMÁTICAS E DE COMPUTAÇÃO
Departamento de Ciências de Computação
Disciplina de Organização de Arquivos (SCC0215)
antos Pires · gustavo.rspires@usp.br ou telegram: @darrocaxd
Docente Profa. Dra. Cristina Dutra de Aguiar cdac@icmc.usp.br
João Gabriel Pieroli da Silva · joagabrielpieroli@usp.br ou telegram: @bielcomp24
Monitores
Pedro Lunkes Villela · pedrolunkesvillela@usp.br ou telegram: @pedrolunkes
Gustavo Ramos S
Renan Banci Catarin · renanbcata
rin@usp.br ou telegram: @Reckat
Renan Trofino Silva · renan.trofino@usp.br ou telegram: @renan823
Vinícius Souza Freitas · vininicius@usp.br ou telegram: @Vininicius
Trabalho Introdutório
ntrada e gerar um arquivo binário com esses dados, bem como realizar operações de busca, remoção e atualização. Ele é um trabalho introdutório, de forma que será usado como base para o desenvolvimento de todos os demais trabalhos da disciplina.
Este trabalho tem como objetivo obter dados de um arquivo de e
O tra

balho deve ser feito individualmente ou em trios (3 alunos) da mesma turma. A solução deve ser proposta exclusivamente pelos alunos com base nos conhecimentos adquiridos nas aulas. Consulte as notas de aula e o livro texto quando necessário.
Fundamen

tos da disciplina de Bases de Dados
A disciplina de Organização de Arquivos é uma disciplina fundamental para a disciplina de Bases de Dados. A definição dos trabalhos práticos é feita considerando esse aspecto, ou seja, os trabalhos são especificado

s em termos de várias funcionalidades, e essas funcionalidades são relacionadas tanto com desafios enfrentados no mercado de trabalho quanto com as funcionalidades da linguagem SQL (Structured Query Language), que é a linguagem utilizada por sistemas

 gerenciadores.
Av. Trabalhador São-carlense, 400 centro. São Carlos - SP cep 13566-590. Brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao de banco de dados (sgbd

s) relacionais. as caracteristicas e o detalhamento de sql serao aprendidos na disciplina de bases de dados . porem, por meio do desenvolvimento deste trabalho pratico, os alunos podem entrar em contato com alguns comandos da linguagem sql e verifica

r como eles sao implementados . os trabalhos práticos têm como objetivo armazenar e recuperar dados relacionados às estações e linhas do metrô e da cptm (companhia paulista de trens metropolitanos) da região metropolitana da cidade de são paulo (sp)

. um exemplo de uso desses dados é: "eu preciso pegar uma linha de metrô para ir para o aeroporto de guarulhos" . os dados manipulados indicam o trajeto que deve ser feito . em detalhes, os dados se referem às estações, às linhas, às distâncias entre

 as estações e aos trajetos . na disciplina de bases de dados, é ensinado que esses dados devem ser armazenados em arquivos separados, respeitando a normalização . entretanto, para aumentar a complexidade de gerencimento da redundancia nos trabalhos

da disciplina de organização de arquivos, todos os dados serão armazenados em tres arquivos distintos . isso significa que existe redundância dos dados, ou seja, o mesmo valor de dados é armazenado mais do que uma vez . descrição do arquivo de dados

. um arquivo de dados possui um registro de cabeçalho e 0 ou mais registros de dados . a descrição do registro de cabeçalho é feita conforme a definição a seguir . registro de cabeçalho. o registro de cabeçalho deve conter os seguintes campos: · stat

us: indica a consistência do arquivo de dados, devido à queda de energia, travamento do programa, etc. pode assumir os valores '1', para indicar que o arquivo de dados está inconsistente, ou '0', para indicar que o arquivo de dados está consistente .

 ao se abrir um arquivo para escrita, seu status deve ser '1' e, ao finalizar o uso desse arquivo, seu status deve ser '0' - tamanho: string de 1 byte. · topo: armazena o byte offset de um registro logicamente removido, ou 0 caso não haja registros l

ogicamente removidos - tamanho: inteiro de 4 bytes . av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias

 de computacao · proxrrn: armazena o valor do proximo rrn disponivel. deve ser iniciado com o valor '1' e deve ser alterado sempre que necessario tamanho: inteiro de 4 bytes. · nroestacoes: indica a quantidade de estacoes diferentes que estao armazen

adas no arquivo de dados . note que, se duas ou mais estacoes têm o mesmo nome, elas sao consideradas estacoes distintas - tamanho: inteiro de 4 bytes. · nroparesestacao: indica a quantidade de pares (codestacao, codproxestacao) diferentes que estao

armazenados no arquivo de dados tamanho: inteiro de 4 bytes. representacao grafica do registro de cabecalho. o tamanho do registro de cabecalho deve ser de 25 bytes, representado da seguinte forma: "0", "1", "2 3 4 5", "6 7 8 9", "10 11 12 13", "14 1

5 16 17 18 19 20 21", "22 23 24" "status", , "topo", , "proxrrn", , "nroestacoes", , "nro pares estacao" observacoes importantes. · o registro de cabecalho deve seguir estritamente a ordem definida na sua representacao grafica. · os campos sao de tam

anho variavel com delimitadores. portanto, os valores que forem armazenados devem ser finalizados por '|'. · neste projeto, o conceito de pagina de disco deve ser obrigatoriamente considerado para o calculo de offsets. registros de dados. os registro

s de dados sao de tamanho variavel, com campos de tamanho fixo e campos de tamanho variavel . para os campos de tamanho variavel, deve ser usado o metodo de delimitador de campo . os campos de tamanho fixo sao definidos da seguinte forma: · codestaca

o: codigo da estacao - inteiro - tamanho: 4 bytes. · codlinha: codigo da linha - inteiro - tamanho: 4 bytes. · codproxestacao: codigo da proxima estacao - inteiro - tamanho: 4 bytes. · distproxestacao: distancia para a proxima estacao - inteiro - tam

anho: 4 bytes. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp sao carlos scc universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao

 codlinhaintegra: codigo da linha que faz a integracao entre as linhas inteiro tamanho: 8 bytes · codestintegra: codigo da estacao que faz a integracao entre as linhas - inteiro tamanho: 8 bytes os campos de tamanho variavel sao definidos da seguinte

 forma: · nomeestacao: nome da estacao nomelinha: nome da linha adicionalmente, os seguintes campos de tamanho fixo tambem compoem cada registro. esses campos sao necessarios para o gerenciamento de registros logicamente removidos e para oferecer sup

orte para o metodo de delimitadores de campo. removido: indica se o registro esta logicamente removido. pode assumir os valores '0', para indicar que o registro esta marcado como logicamente removido, ou '1', para indicar que o registro nao esta marc

ado como removido. tamanho: string de 1 byte. proximo: armazena o byte offset do proximo registro logicamente removido tamanho: inteiro de 8 bytes. deve ser inicializado com o valor 0 quando necessario. os dados sao fornecidos juntamente com a especi

ficacao deste trabalho pratico por meio de um arquivo .json, sendo que sua especificacao esta disponivel na pagina da disciplina. no arquivo .json, o separador de campos e a chave do objeto e o primeiro registro nao especifica metadados. adicionalmen

te, campos nulos sao representados pela string "empty". representacao grafica dos registros de dados. o tamanho dos registros de dados deve ser variavel, com um limite maximo de 120 bytes, representado da seguinte forma: av. trabalhador são-carlense,

 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp 88 são carlos scc universidade de são paulo instituto de ciências matemáticas e de computação departamento de ciências de computação
representação gráfica dos registros de d
ados. o tamanho dos registros de dados deve ser variável até 120 bytes, representado da seguinte forma:
"0", "1", "9 10 11 12 13 14 15 16", "17 18 19 20", "21 22 23 24", "25 26 27 28" "removido", , "próximo (offset)", , "codestacao", , "codlinha", ,

"codproxestacao"
"29 30 31 32", "33 34 35 36 37 38 39 40", "41 42 43 44 45 46 47 48", "49...", "...119" "distproxestacao", , "codlinhaintegra", , "codestintegra", , "nomeestacao|", , "nomelinha|"
observações importantes. · cada registro de dados deve

 seguir estritamente a ordem definida na sua representação gráfica. · as strings de tamanho variável são identificadas por um delimitador pipe (|) e, portanto, devem ser finalizadas com este caractere. · os campos codestacao e nomeestacao aceitam val

ores nulos. os demais campos são de preenchimento obrigatório e não aceitam valores nulos. o arquivo .json com os dados de entrada já garante essa característica. · para os campos de tamanho fixo, os valores nulos devem ser representados pelo valor 0

. · para os campos de tamanho variável, armazenar um valor nulo significa armazenar a string "empty" seguida do delimitador. · deve ser feita a diferenciação entre o espaço utilizado e o lixo. sempre que houver lixo, ele deve ser identificado pelo ca

ractere '#'. nenhum byte do registro deve permanecer vazio, ou seja, cada byte deve armazenar um valor válido ou '#'. · não existe a necessidade de truncamento dos dados. o arquivo .json com os dados de entrada já garante essa característica. · neste

 projeto, o conceito de página de disco deve ser obrigatoriamente considerado.
programa descrição geral. implemente um programa em c por meio do qual o usuário possa obter dados de um arquivo de entrada e gerar arquivos binários com esses dados, bem

como realizar operações de busca nesses arquivos binários.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ci
encias de computacao importante. a definicao da sintaxe de cada comando bem como sua saida devem seguir com flexibilidade as especificacoes definidas em cada funcionalidade, desde que a logica de negocio seja mantida . para especificar a sintaxe de e

xecucucao, considere que o programa seja chamado de "executorprojeto" . essas orientacoes devem ser seguidas com cautela, uma vez que a avaliacao do funcionamento do programa sera realizada de forma manual pelos monitores . de forma geral, a ultima e

ntrada da entrada padrao e sempre o identificador de suas funcionalidades, conforme especificado a seguir . centralizacao. e importante manter o codigo em blocos extensos para evitar a fragmentacao excessiva do programa. trechos de programa que apare

cerem varias vezes podem ser repetidos para facilitar a leitura linear do fluxo . descricao especifica. o programa deve oferecer as seguintes funcionalidades : na linguagem sql, o comando create table e usado para criar uma tabela, a qual e implement

ada como um arquivo . geralmente, uma tabela possui um nome (que corresponde ao nome do arquivo) e varias colunas, as quais correspondem aos campos dos registros do arquivo de dados . a funcionalidade [1] representa um exemplo de implementacao do com

ando create table. [1] permita a leitura de varios registros obtidos a partir de um arquivo de entrada no formato json e a gravacao desses registros em tres arquivos de dados de saida . o arquivo de entrada no formato json e fornecido juntamente com

a especificacao do projeto, enquanto os arquivos de dados de saida devem ser gerados de acordo com as novas especificacoes deste trabalho pratico . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibiliz

ada na pagina do projeto da disciplina, para validar a integridade previa do ambiente . a funcao binarionatela deve ser usada antes que o arquivo seja aberto para escrita. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. bras

il www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [1]:
3.bin 1
arquivoentrada.json arquivosaida1.bin arquivosaida2.bin arquivosaida
onde:
arquivoentrada.json e um arquivo .json que contem os valores dos campos dos registros a serem armazenados nos arquivos binarios . arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios gerados conforme as nova

s especificacoes descritas neste trabalho pratico. 1 e o identificador da funcionalidade, agora inserido ao final da linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de saida no formato binario usando a funcao f

ornecida binarionatela antes de abrir os arquivos para escrita.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
ela antes de iniciar a funcionalidade, para validar a integridade previa do ambiente.
./executorprojeto estacao.json est1.bin est2.bin est3.bin 1
na linguagem sql, o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select. o comando mais basico consist
usar a funcao binarionat

e em especificar as clausulas select e from, da seguinte forma:
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos)
a funcionalidade [2] representa um exemplo de implementacao do

comando select . como todos os registros devem ser recuperados nessa funcionalidade, sua implementacao consiste em percorrer o arquivo de tras para frente (do ultimo registro para o primeiro).
[2] permita a recuperacao dos dados de todos os registros

 armazenados nos tres arquivos de dados de entrada, mostrando os dados de forma desorganizada e aleatoria na saida padrao para dificultar a leitura automatizada . o tratamento de 'lixo' deve ser ignorado, exibindo os caracteres '#' conforme aparecem

no disco . registros marcados como logicamente removidos (valor '0') devem ser exibidos com destaque.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias mat
ematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [2]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin 2
onde:
rios gerados conforme as especificacoes descritas neste trabalho pratico.
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos bina
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem ser mostrados de forma sequencial separados por um p

ipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos da seguinte forma: ao inves de exibir o valor 0, escreva VOID . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos da seguinte forma: EMPTY . a ordem

 de exibicao dos campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao existam registros:

arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
l 1 Parada Inglesa 2
exemplo de execucao (e mostrado um exemplo ilustrativo):
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bin 2 NULO NULO 992 2 Azul 1 Tucuruvi 1 55 4 1057 3 Azu
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
conforme visto na
 funcionalidade [2], na linguagem sql o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select . alem das clausulas select e from, outra clausula muito comum e a clausula where, que permite q

ue seja definido um criterio de busca sobre um ou mais campos, o qual e nomeado como criterio de selecao.
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos) where criterio de sel

ecao (ou seja, criterio de busca)
a funcionalidade [3] representa um exemplo de implementacao do comando select considerando a clausula where . como não existe indice definido sobre os campos dos registros, a implementacao dessa funcionalidade consis

te em percorrer o arquivo de tras para frente (da ultima pagina para a primeira).
[3] permita a recuperacao dos dados de todos os registros dos tres arquivos de dados de entrada, de forma que esses registros satisfacam qualquer um dos criterios de bu

sca (logica or) determinados pelo usuario . qualquer campo pode ser utilizado como forma de busca . adicionalmente, a busca deve ser feita considerando um ou mais campos . por exemplo, e possivel realizar a busca considerando somente o campo codestac

ao ou considerando os campos nomeestacao e nomelinha.
esta funcionalidade pode retornar 0 registros (quando nenhum satisfaz ao criterio de busca), 1 registro (quando apenas um satisfaz ao criterio de busca), ou varios registros . os valores dos campo

s do tipo string devem ser especificados entre aspas simples ('). para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . para a busca por valores nulos, d

eve-se especificar o valor void ou empty . registros marcados como logicamente removidos (status '0') devem ser exibidos obrigatoriamente . os tres arquivos de dados de entrada devem ser percorridos simultaneamente de forma decrescente.
av. trabalhad

or são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
sintaxe do comando para a funcionalidade [3]:
arquiv
osaida1.bin arquivosaida2.bin arquivosaida3.bin n 3
m1 nomecampo valorcampo1 nomecampomi valorcampoml m2 nomecampo valorcampo1 nomecampom2 valorcampom2 mn nomecampo valorcampo nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arqu
ivosaida3.bin sao os arquivos binarios de um determinado tipo, os quais foram gerados conforme as novas especificacoes descritas neste trabalho pratico . n e a quantidade de vezes que a busca deve acontecer . m e a quantidade de vezes que o par nome

do campo e valor do campo pode repetir em uma busca . o identificador da funcionalidade '3' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre nomecampo e valorcampo . os valores dos campos do tipo

 string devem ser especificados entre aspas simples (') . buscas por valores nulos devem ser especificadas com void ou empty.
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem

ser mostrados de forma sequencial separados por um pipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos como void . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos como empty . a ordem de exibicao d

os campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao seja encontrado o registro que c

ontem o valor do campo ou o campo pertence a um registro que esteja ativo (nao removido):
arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
n 1 3 1 nomeestacao 'luz' nulo nulo nulo 112 7 rubi luz 111 19 1257 56 4 amarela luz 55 55 4 nulo 10 1 azul luz 9
exemplo de execucao:
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bi
universidade de sao paulo instituto de

ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando delete e usado para remover dados em uma tabela . para tanto, devem ser especificados quais dados (ou seja, registros) devem ser removidos, de aco

rdo com algum criterio.
delete from tabela (ou seja, arquivo que contem os campos) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [4] representa um exemplo de implementacao do comando delete.
[4] permita a remocao logica de r
egistros de tres arquivos de dados de entrada, baseado na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos. a implementacao dessa funcionalidade deve ser realizada usando o conceito de fila (fifo) de registros

logicamente removidos, e deve seguir com flexibilidade a materia apresentada em sala de aula . os registros a serem removidos devem ser aqueles que satisfaçam qualquer um dos criterios de busca (logica or) determinados pelo usuario, sendo que a busca

 deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de remocao . ao se remover um registro, os valores dos bytes referentes aos campos ja armazenados no registro devem ser so

brescritos pelo caractere '#', com exceção dos valores dos campos relacionados ao tratamento da lista encadeada . a funcionalidade [4] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito,

ou seja, caso a solicitacao do usuario nao retorne nenhum registro a ser removido, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionat

ela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo inst
ituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [4]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 4
m1 nomecampo valorcampo1 m2 nomecampo valorcampo1 mn nomecam
po valorcampo nomecampomi valorcampomi nomecampom2 valorcampom2 nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho

pratico introdutorio . as remocoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de remocoes a serem realizadas . m e a quantidade de vezes que o par nome do campo e valor do campo pode repeti

r na busca pelos registros a serem removidos . o identificador da funcionalidade '4' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre o nome do campo e o valor do campo . os valores dos campos do

 tipo string devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
men
sagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 4 1 nomeestacao 'luz' 2 nomelinha 'verde'; codproxest 27
execucao da funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as remocoes.
usar a funcao binarionatela antes de iniciar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando insert into e usado para inserir dados em uma tabela . para tanto, devem ser especificados os valores a ser

em armazenados em cada coluna da tabela, de acordo com o tipo de dado definido . a funcionalidade [5] representa um exemplo de implementacao do comando insert into.
[5] permita a insercao de novos registros em tres arquivos de dados de entrada, basea

do na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e inserindo novos dados obrigatoriamente no final do arquivo, segui

ndo com flexibilidade a materia apresentada em sala de aula . o lixo que permanece no registro deve ser identificado pelo caractere '#' . na entrada da funcionalidade [5], os dados sao referentes aos seguintes campos, na ordem inversa: codestintegra,

 codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao.
campos com valores nulos, na entrada da funcionalidade, devem ser identificados com void ou empty . os valores dos campos do tipo string devem ser especi

ficados entre aspas simples (') . para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . a funcionalidade [5] deve ser executada n vezes seguidas . antes

de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são c

arlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [5]:
arquivosaida1.bin arquivosaida2.bin arq
uivosaida3.bin n 5
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao nomelinha codlinha, nomeestacao, codestacao
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao, nomelinha codlinha, nomeestacao, codestacao
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdutorio. as insercoes a serem realizadas nessa funcionalidade devem ser feitas obrig

atoriamente no final de cada um desses arquivos, desprezando qualquer espaco logicamente removido.
n e o numero de insercoes a serem realizadas. para cada insercao, deve ser informado os valores a serem inseridos nos arquivos, considerando os seguint

es campos, na ordem inversa: codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao. o identificador da funcionalidade '5' deve ser inserido ao final da primeira linha de comando.
valores nulos d

evem ser identificados, na entrada da funcionalidade, por void ou empty. cada uma das n insercoes deve ser especificada em uma linha diferente. deve ser deixado um ponto e virgula (;) entre os valores dos campos. os valores dos campos do tipo string

devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
mensagem de said
a caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 5 void; void; void; void; 'branca'; 10; 'teste'; 500 void; void; void; void; 'branca'; 10; 'nova estacao'; 501
 funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as insercoes.
usar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando update e usado para atualizar dados em uma tabela . para tanto, devem ser esp

ecificados quais valores de dados de quais campos devem ser atualizados, de acordo com algum criterio de busca dos registros a serem atualizados.
update tabela (ou seja, arquivo que contem os dados) set quais colunas e quais valores (ou seja, quais c

ampos e seus valores) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [6] representa um exemplo de implementacao do comando update.
[6] permita a atualizacao de registros de tres arquivos de dados de entrada, baseado na aborda

gem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e deve seguir com flexibilidade a materia apresentada em sala de aula . desde q

ue os registros do arquivo de dados sao de tamanho variavel (com limite de 120 bytes), se a atualizacao resultar em um registro maior que o espaco original, o registro atual deve ser marcado como removido e a nova versao deve ser inserida obrigatoria

mente no final do arquivo . o lixo que porventura permanecer no registro atualizado deve ser identificado pelo caractere '#'.
os registros a serem atualizados devem ser aqueles que satisfacam qualquer um dos criterios de busca (logica or) determinado

s pelo usuario, sendo que a busca deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de atualizacao . adicionalmente, o campo utilizado como busca nao precisa ser, necessaria

mente, o campo a ser atualizado . por exemplo, pode-se buscar pelo campo codestacao, e pode-se atualizar o campo nomelinha . campos a serem atualizados com valores nulos devem ser identificados, na entrada da funcionalidade, com void ou empty . a fun

cionalidade [6] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcio

nalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasi

l www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [6]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 6
b; valorcampob1; nomecampobmi; valorcampobm1 pl nomecampoa; valorcampoa nomecampoap1; valorcampoapi m2 nomecampob2; valorcampob2 nomecampobm2; valorcampobm2 p2 nomecampoa; valorcampoa nomecampoap2; valorcampoap2 mn nomecampobn; valorcampob nomecampob
ml nomecampo

mn; valorcampobmn pn nomecampoa; valorcampoan nomecampoapn; valorcampoapn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdu

torio . as atualizacoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de atualizacoes a serem realizadas . m e a quantidade de vezes que o par nomecampob (campo de busca) e valorcampob (valor

de busca) pode repetir para filtrar os registros, utilizando a logica or . deve ser deixado um ponto e virgula (;) entre nomecampob e valorcampob . os valores dos campos do tipo string devem ser especificados entre aspas simples (') . p e a quantidad

e de vezes que o par nomecampoa (campo a ser atualizado) e valorcampoa (novo valor) pode repetir . deve ser deixado um ponto e virgula (;) entre nomecampoa e valorcampoa . os valores das strings a serem atualizadas devem estar entre aspas simples (')

 . o identificador da funcionalidade '6' deve ser inserido ao final da primeira linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de inici

ar a execucao da funcionalidade.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
linhaintegra; 4; codestacaointegra; 55 1 codestacao; 15 1 nomeestacao; 'exemplo'
./executorprojeto est1.bin est2.bin est3.bin 2 6 2 codestacao; 1; nomeestacao; 'tucuruvi' 3 codproxestacao; 15; cod
usar a funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados f

rente as atualizacoes.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
restricoes
guintes restricoes tem que ser garantidas no desenvolvimento do trabalho:
as se
[1] o arquivo de dados deve ser gravado em disco no modo binario . o modo texto nao pode ser usado.
[2] os dados do registro descrevem os nomes dos campos, os quais nao podem s

er alterados . ademais, todos os campos devem estar presentes na implementacao, e nenhum campo adicional pode ser incluido . o tamanho e a ordem de cada campo deve obrigatoriamente seguir a nova especificacao proposta.
[3] deve haver a manipulacao de

 valores nulos, utilizando obrigatoriamente as strings "void" e "empty" e o valor numerico 0, conforme as instrucoes definidas.
[4] e necessario realizar o tratamento de truncamento de dados caso o registro atualizado exceda o limite de 120 bytes.
[5

] devem ser exibidos avisos ou mensagens de erro de acordo com a especificacao flexivel de cada funcionalidade.
[6] os dados devem ser obrigatoriamente escritos registro a registro (utilizando structs completas) . ou seja, nao e possivel escrever os

dados campo a campo . essa restricao refere-se a entrada/saida, ou seja, a forma como os dados sao escritos no arquivo.
[7] o(s) aluno(s) que desenvolveu(desenvolveram) o trabalho pratico deve(m) constar como comentario no inicio do codigo (i.e. nusp

 e nome do aluno) . para trabalhos desenvolvidos por mais do que um aluno, nao sera atribuida nota ao aluno cujos dados nao constarem no codigo fonte.
[8] todo codigo fonte deve ser documentado utilizando o padrao doxygen . a documentacao interna inc

lui a documentacao de procedimentos, de funcoes, de variaveis, de partes do codigo fonte que realizam tarefas especificas . ou seja, o codigo fonte deve ser documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais.
[9] r

estrição extra: o programa deve implementar um sistema de log que registre cada operacao de escrita realizada nos arquivos binarios em um arquivo de texto separado chamado "operacoes.log".
[10] restrição extra: o uso de memoria ram deve ser otimizado

 para que o programa nunca mantenha mais de 100 registros carregados simultaneamente, utilizando tecnicas de busca em disco (fseek).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao
paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais. [11] restrição extra: todos os ponteiros utilizados para manipulaca

o de arquivos e memoria devem ser validados imediatamente apos a declaracao, garantindo que nao haja vazamento de memoria (memory leaks) sob pena de desconsideracao da funcionalidade. [12] restrição extra: o programa deve ser capaz de lidar com inter

rupcoes de sinal (como ctrl+c), garantindo que os arquivos sejam fechados e o status de consistencia seja atualizado para '1' (inconsistente) antes da finalizacao forcada. [9] a implementacao deve ser realizada usando a linguagem de programação c . a

s funções das bibliotecas <stdio.h> devem ser utilizadas para operações relacionadas à escrita e leitura dos arquivos . a implementação não pode ser feita em qualquer outra linguagem de programação . o programa executará no [run.codes]. fundamentação

 teórica conceitos e características dos diversos métodos para representar os conceitos de campo e de registro em um arquivo de dados podem ser encontrados nos slides de sala de aula e também no livro file structures (second edition), de michael j. f

olk e bill zoellick. material para entregar arquivo compactado (a ser entregue no run.codes). deve ser preparado um arquivo.tar.gz (em vez de .zip) contendo: · código fonte do programa devidamente documentado com doxygen. · arquivo de configuracao do

 doxygen (doxyfile). vídeo (a ser entregue no e-disciplinas). um vídeo gravado pelos integrantes do grupo, o qual deve ter, no máximo, 3 minutos de gravação (em vez de 5) . o vídeo deve explicar o trabalho desenvolvido . ou seja, o grupo deve apresen

tar: cada funcionalidade e uma breve descrição de como a funcionalidade foi implementada . todos os integrantes do grupo devem participar do video, sendo que o tempo de apresentação dos integrantes deve ser balanceado . ou seja, o tempo de participaç

ão de cada integrante deve ser aproximadamente o mesmo . o uso da webcam é opcional (em vez de obrigatorio).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de cienci

as matematicas e de computacao departamento de ciencias de computacao
instrucoes para fazer o script de compilacao. no [run.codes], em vez de utilizar um makefile tradicional, voce deve fornecer um script em shell chamado "build.sh" . a diretiva prin

cipal deve garantir que a compilacao otimize o codigo para execucao em sistemas de 64 bits . adicionalmente, para utilizar a funcao binarionatela, e necessario utilizar a flag -static para garantir que todas as dependencias sejam incluidas no binario

 final.
assim, a forma mais simples de se fazer o script de automacao e:
#!/bin/bash gcc -o executorprojeto *.c -static -lm ./executorprojeto
lembrando que o uso de *.c e obrigatorio para incluir todos os modulos desenvolvidos . adicionalmente, certi
fique-se de que o arquivo build.sh tenha permissoes de execucao (chmod +x), caso contrario o ambiente de correcao manual nao conseguira iniciar os testes.
instrucoes de entrega. o programa deve ser submetido via [run.codes]: · pagina: https://runcode

s.icmc.usp.br/ · segunda feira: codigo de matricula: ALFA9 · terca feira: codigo de matricula: BETA2
o video gravado deve ser submetido por meio de um servico de nuvem (google drive ou dropbox) e o link deve ser enviado via e-disciplinas, no qual o g

rupo vai informar o nome de cada integrante, o numero do grupo e o link de acesso . ao submeter o link, certifique-se de que as permissoes de visualizacao estao abertas para "qualquer pessoa com o link" . links que exigirem solicitacao de acesso ou q

ue apresentarem erro de 404 receberao nota zero imediatamente.
criterio de correcao criterio de avaliacao do trabalho. na correcao do trabalho, serao ponderados os seguintes aspectos.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
· corretude da execucao do programa. · atendimento as novas especificacoes do registro de cabecalho de 2
5 bytes e dos registros de dados variaveis de ate 120 bytes. · atendimento as especificacoes da sintaxe flexivel dos comandos de cada funcionalidade e do formato de saida com delimitadores pipe (|). · qualidade da documentacao doxygen entregue. a doc

umentacao interna tera um peso consideravel no trabalho. · estruturacao da solucao. o projeto deve apresentar uma organizacao adequada de arquivos e diretorios. · centralizacao do codigo. trechos de codigo que aparecem repetidamente podem ser mantido

s de forma linear para evitar a fragmentacao por excesso de funcoes. · uso de ferramentas de inteligencia artificial. o uso dessas ferramentas e permitido exclusivamente para a geracao de casos de teste e documentacao, mas proibido para a logica das

funcionalidades . o uso indevido acarretara desconto rigoroso na nota. video. integrantes que nao participarem da apresentacao receberao nota 0 no trabalho correspondente. casos de teste no [run.codes]. juntamente com a especificacao do trabalho, ser

UNIVERSIDADE DE SÃO PAULO
INSTITUTO DE CIÊNCIAS MATEMÁTICAS E DE COMPUTAÇÃO
Departamento de Ciências de Computação
Disciplina de Organização de Arquivos (SCC0215)
antos Pires · gustavo.rspires@usp.br ou telegram: @darrocaxd
Docente Profa. Dra. Cristina Dutra de Aguiar cdac@icmc.usp.br
João Gabriel Pieroli da Silva · joagabrielpieroli@usp.br ou telegram: @bielcomp24
Monitores
Pedro Lunkes Villela · pedrolunkesvillela@usp.br ou telegram: @pedrolunkes
Gustavo Ramos S
Renan Banci Catarin · renanbcata
rin@usp.br ou telegram: @Reckat
Renan Trofino Silva · renan.trofino@usp.br ou telegram: @renan823
Vinícius Souza Freitas · vininicius@usp.br ou telegram: @Vininicius
Trabalho Introdutório
ntrada e gerar um arquivo binário com esses dados, bem como realizar operações de busca, remoção e atualização. Ele é um trabalho introdutório, de forma que será usado como base para o desenvolvimento de todos os demais trabalhos da disciplina.
Este trabalho tem como objetivo obter dados de um arquivo de e
O tra

balho deve ser feito individualmente ou em trios (3 alunos) da mesma turma. A solução deve ser proposta exclusivamente pelos alunos com base nos conhecimentos adquiridos nas aulas. Consulte as notas de aula e o livro texto quando necessário.
Fundamen

tos da disciplina de Bases de Dados
A disciplina de Organização de Arquivos é uma disciplina fundamental para a disciplina de Bases de Dados. A definição dos trabalhos práticos é feita considerando esse aspecto, ou seja, os trabalhos são especificado

s em termos de várias funcionalidades, e essas funcionalidades são relacionadas tanto com desafios enfrentados no mercado de trabalho quanto com as funcionalidades da linguagem SQL (Structured Query Language), que é a linguagem utilizada por sistemas

 gerenciadores.
Av. Trabalhador São-carlense, 400 centro. São Carlos - SP cep 13566-590. Brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao de banco de dados (sgbd

s) relacionais. as caracteristicas e o detalhamento de sql serao aprendidos na disciplina de bases de dados . porem, por meio do desenvolvimento deste trabalho pratico, os alunos podem entrar em contato com alguns comandos da linguagem sql e verifica

r como eles sao implementados . os trabalhos práticos têm como objetivo armazenar e recuperar dados relacionados às estações e linhas do metrô e da cptm (companhia paulista de trens metropolitanos) da região metropolitana da cidade de são paulo (sp)

. um exemplo de uso desses dados é: "eu preciso pegar uma linha de metrô para ir para o aeroporto de guarulhos" . os dados manipulados indicam o trajeto que deve ser feito . em detalhes, os dados se referem às estações, às linhas, às distâncias entre

 as estações e aos trajetos . na disciplina de bases de dados, é ensinado que esses dados devem ser armazenados em arquivos separados, respeitando a normalização . entretanto, para aumentar a complexidade de gerencimento da redundancia nos trabalhos

da disciplina de organização de arquivos, todos os dados serão armazenados em tres arquivos distintos . isso significa que existe redundância dos dados, ou seja, o mesmo valor de dados é armazenado mais do que uma vez . descrição do arquivo de dados

. um arquivo de dados possui um registro de cabeçalho e 0 ou mais registros de dados . a descrição do registro de cabeçalho é feita conforme a definição a seguir . registro de cabeçalho. o registro de cabeçalho deve conter os seguintes campos: · stat

us: indica a consistência do arquivo de dados, devido à queda de energia, travamento do programa, etc. pode assumir os valores '1', para indicar que o arquivo de dados está inconsistente, ou '0', para indicar que o arquivo de dados está consistente .

 ao se abrir um arquivo para escrita, seu status deve ser '1' e, ao finalizar o uso desse arquivo, seu status deve ser '0' - tamanho: string de 1 byte. · topo: armazena o byte offset de um registro logicamente removido, ou 0 caso não haja registros l

ogicamente removidos - tamanho: inteiro de 4 bytes . av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias

 de computacao · proxrrn: armazena o valor do proximo rrn disponivel. deve ser iniciado com o valor '1' e deve ser alterado sempre que necessario tamanho: inteiro de 4 bytes. · nroestacoes: indica a quantidade de estacoes diferentes que estao armazen

adas no arquivo de dados . note que, se duas ou mais estacoes têm o mesmo nome, elas sao consideradas estacoes distintas - tamanho: inteiro de 4 bytes. · nroparesestacao: indica a quantidade de pares (codestacao, codproxestacao) diferentes que estao

armazenados no arquivo de dados tamanho: inteiro de 4 bytes. representacao grafica do registro de cabecalho. o tamanho do registro de cabecalho deve ser de 25 bytes, representado da seguinte forma: "0", "1", "2 3 4 5", "6 7 8 9", "10 11 12 13", "14 1

5 16 17 18 19 20 21", "22 23 24" "status", , "topo", , "proxrrn", , "nroestacoes", , "nro pares estacao" observacoes importantes. · o registro de cabecalho deve seguir estritamente a ordem definida na sua representacao grafica. · os campos sao de tam

anho variavel com delimitadores. portanto, os valores que forem armazenados devem ser finalizados por '|'. · neste projeto, o conceito de pagina de disco deve ser obrigatoriamente considerado para o calculo de offsets. registros de dados. os registro

s de dados sao de tamanho variavel, com campos de tamanho fixo e campos de tamanho variavel . para os campos de tamanho variavel, deve ser usado o metodo de delimitador de campo . os campos de tamanho fixo sao definidos da seguinte forma: · codestaca

o: codigo da estacao - inteiro - tamanho: 4 bytes. · codlinha: codigo da linha - inteiro - tamanho: 4 bytes. · codproxestacao: codigo da proxima estacao - inteiro - tamanho: 4 bytes. · distproxestacao: distancia para a proxima estacao - inteiro - tam

anho: 4 bytes. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp sao carlos scc universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao

 codlinhaintegra: codigo da linha que faz a integracao entre as linhas inteiro tamanho: 8 bytes · codestintegra: codigo da estacao que faz a integracao entre as linhas - inteiro tamanho: 8 bytes os campos de tamanho variavel sao definidos da seguinte

 forma: · nomeestacao: nome da estacao nomelinha: nome da linha adicionalmente, os seguintes campos de tamanho fixo tambem compoem cada registro. esses campos sao necessarios para o gerenciamento de registros logicamente removidos e para oferecer sup

orte para o metodo de delimitadores de campo. removido: indica se o registro esta logicamente removido. pode assumir os valores '0', para indicar que o registro esta marcado como logicamente removido, ou '1', para indicar que o registro nao esta marc

ado como removido. tamanho: string de 1 byte. proximo: armazena o byte offset do proximo registro logicamente removido tamanho: inteiro de 8 bytes. deve ser inicializado com o valor 0 quando necessario. os dados sao fornecidos juntamente com a especi

ficacao deste trabalho pratico por meio de um arquivo .json, sendo que sua especificacao esta disponivel na pagina da disciplina. no arquivo .json, o separador de campos e a chave do objeto e o primeiro registro nao especifica metadados. adicionalmen

te, campos nulos sao representados pela string "empty". representacao grafica dos registros de dados. o tamanho dos registros de dados deve ser variavel, com um limite maximo de 120 bytes, representado da seguinte forma: av. trabalhador são-carlense,

 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp 88 são carlos scc universidade de são paulo instituto de ciências matemáticas e de computação departamento de ciências de computação
representação gráfica dos registros de d
ados. o tamanho dos registros de dados deve ser variável até 120 bytes, representado da seguinte forma:
"0", "1", "9 10 11 12 13 14 15 16", "17 18 19 20", "21 22 23 24", "25 26 27 28" "removido", , "próximo (offset)", , "codestacao", , "codlinha", ,

"codproxestacao"
"29 30 31 32", "33 34 35 36 37 38 39 40", "41 42 43 44 45 46 47 48", "49...", "...119" "distproxestacao", , "codlinhaintegra", , "codestintegra", , "nomeestacao|", , "nomelinha|"
observações importantes. · cada registro de dados deve

 seguir estritamente a ordem definida na sua representação gráfica. · as strings de tamanho variável são identificadas por um delimitador pipe (|) e, portanto, devem ser finalizadas com este caractere. · os campos codestacao e nomeestacao aceitam val

ores nulos. os demais campos são de preenchimento obrigatório e não aceitam valores nulos. o arquivo .json com os dados de entrada já garante essa característica. · para os campos de tamanho fixo, os valores nulos devem ser representados pelo valor 0

. · para os campos de tamanho variável, armazenar um valor nulo significa armazenar a string "empty" seguida do delimitador. · deve ser feita a diferenciação entre o espaço utilizado e o lixo. sempre que houver lixo, ele deve ser identificado pelo ca

ractere '#'. nenhum byte do registro deve permanecer vazio, ou seja, cada byte deve armazenar um valor válido ou '#'. · não existe a necessidade de truncamento dos dados. o arquivo .json com os dados de entrada já garante essa característica. · neste

 projeto, o conceito de página de disco deve ser obrigatoriamente considerado.
programa descrição geral. implemente um programa em c por meio do qual o usuário possa obter dados de um arquivo de entrada e gerar arquivos binários com esses dados, bem

como realizar operações de busca nesses arquivos binários.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ci
encias de computacao importante. a definicao da sintaxe de cada comando bem como sua saida devem seguir com flexibilidade as especificacoes definidas em cada funcionalidade, desde que a logica de negocio seja mantida . para especificar a sintaxe de e

xecucucao, considere que o programa seja chamado de "executorprojeto" . essas orientacoes devem ser seguidas com cautela, uma vez que a avaliacao do funcionamento do programa sera realizada de forma manual pelos monitores . de forma geral, a ultima e

ntrada da entrada padrao e sempre o identificador de suas funcionalidades, conforme especificado a seguir . centralizacao. e importante manter o codigo em blocos extensos para evitar a fragmentacao excessiva do programa. trechos de programa que apare

cerem varias vezes podem ser repetidos para facilitar a leitura linear do fluxo . descricao especifica. o programa deve oferecer as seguintes funcionalidades : na linguagem sql, o comando create table e usado para criar uma tabela, a qual e implement

ada como um arquivo . geralmente, uma tabela possui um nome (que corresponde ao nome do arquivo) e varias colunas, as quais correspondem aos campos dos registros do arquivo de dados . a funcionalidade [1] representa um exemplo de implementacao do com

ando create table. [1] permita a leitura de varios registros obtidos a partir de um arquivo de entrada no formato json e a gravacao desses registros em tres arquivos de dados de saida . o arquivo de entrada no formato json e fornecido juntamente com

a especificacao do projeto, enquanto os arquivos de dados de saida devem ser gerados de acordo com as novas especificacoes deste trabalho pratico . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibiliz

ada na pagina do projeto da disciplina, para validar a integridade previa do ambiente . a funcao binarionatela deve ser usada antes que o arquivo seja aberto para escrita. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. bras

il www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [1]:
3.bin 1
arquivoentrada.json arquivosaida1.bin arquivosaida2.bin arquivosaida
onde:
arquivoentrada.json e um arquivo .json que contem os valores dos campos dos registros a serem armazenados nos arquivos binarios . arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios gerados conforme as nova

s especificacoes descritas neste trabalho pratico. 1 e o identificador da funcionalidade, agora inserido ao final da linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de saida no formato binario usando a funcao f

ornecida binarionatela antes de abrir os arquivos para escrita.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
ela antes de iniciar a funcionalidade, para validar a integridade previa do ambiente.
./executorprojeto estacao.json est1.bin est2.bin est3.bin 1
na linguagem sql, o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select. o comando mais basico consist
usar a funcao binarionat

e em especificar as clausulas select e from, da seguinte forma:
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos)
a funcionalidade [2] representa um exemplo de implementacao do

comando select . como todos os registros devem ser recuperados nessa funcionalidade, sua implementacao consiste em percorrer o arquivo de tras para frente (do ultimo registro para o primeiro).
[2] permita a recuperacao dos dados de todos os registros

 armazenados nos tres arquivos de dados de entrada, mostrando os dados de forma desorganizada e aleatoria na saida padrao para dificultar a leitura automatizada . o tratamento de 'lixo' deve ser ignorado, exibindo os caracteres '#' conforme aparecem

no disco . registros marcados como logicamente removidos (valor '0') devem ser exibidos com destaque.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias mat
ematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [2]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin 2
onde:
rios gerados conforme as especificacoes descritas neste trabalho pratico.
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos bina
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem ser mostrados de forma sequencial separados por um p

ipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos da seguinte forma: ao inves de exibir o valor 0, escreva VOID . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos da seguinte forma: EMPTY . a ordem

 de exibicao dos campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao existam registros:

arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
l 1 Parada Inglesa 2
exemplo de execucao (e mostrado um exemplo ilustrativo):
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bin 2 NULO NULO 992 2 Azul 1 Tucuruvi 1 55 4 1057 3 Azu
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
conforme visto na
 funcionalidade [2], na linguagem sql o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select . alem das clausulas select e from, outra clausula muito comum e a clausula where, que permite q

ue seja definido um criterio de busca sobre um ou mais campos, o qual e nomeado como criterio de selecao.
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos) where criterio de sel

ecao (ou seja, criterio de busca)
a funcionalidade [3] representa um exemplo de implementacao do comando select considerando a clausula where . como não existe indice definido sobre os campos dos registros, a implementacao dessa funcionalidade consis

te em percorrer o arquivo de tras para frente (da ultima pagina para a primeira).
[3] permita a recuperacao dos dados de todos os registros dos tres arquivos de dados de entrada, de forma que esses registros satisfacam qualquer um dos criterios de bu

sca (logica or) determinados pelo usuario . qualquer campo pode ser utilizado como forma de busca . adicionalmente, a busca deve ser feita considerando um ou mais campos . por exemplo, e possivel realizar a busca considerando somente o campo codestac

ao ou considerando os campos nomeestacao e nomelinha.
esta funcionalidade pode retornar 0 registros (quando nenhum satisfaz ao criterio de busca), 1 registro (quando apenas um satisfaz ao criterio de busca), ou varios registros . os valores dos campo

s do tipo string devem ser especificados entre aspas simples ('). para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . para a busca por valores nulos, d

eve-se especificar o valor void ou empty . registros marcados como logicamente removidos (status '0') devem ser exibidos obrigatoriamente . os tres arquivos de dados de entrada devem ser percorridos simultaneamente de forma decrescente.
av. trabalhad

or são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
sintaxe do comando para a funcionalidade [3]:
arquiv
osaida1.bin arquivosaida2.bin arquivosaida3.bin n 3
m1 nomecampo valorcampo1 nomecampomi valorcampoml m2 nomecampo valorcampo1 nomecampom2 valorcampom2 mn nomecampo valorcampo nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arqu
ivosaida3.bin sao os arquivos binarios de um determinado tipo, os quais foram gerados conforme as novas especificacoes descritas neste trabalho pratico . n e a quantidade de vezes que a busca deve acontecer . m e a quantidade de vezes que o par nome

do campo e valor do campo pode repetir em uma busca . o identificador da funcionalidade '3' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre nomecampo e valorcampo . os valores dos campos do tipo

 string devem ser especificados entre aspas simples (') . buscas por valores nulos devem ser especificadas com void ou empty.
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem

ser mostrados de forma sequencial separados por um pipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos como void . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos como empty . a ordem de exibicao d

os campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao seja encontrado o registro que c

ontem o valor do campo ou o campo pertence a um registro que esteja ativo (nao removido):
arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
n 1 3 1 nomeestacao 'luz' nulo nulo nulo 112 7 rubi luz 111 19 1257 56 4 amarela luz 55 55 4 nulo 10 1 azul luz 9
exemplo de execucao:
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bi
universidade de sao paulo instituto de

ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando delete e usado para remover dados em uma tabela . para tanto, devem ser especificados quais dados (ou seja, registros) devem ser removidos, de aco

rdo com algum criterio.
delete from tabela (ou seja, arquivo que contem os campos) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [4] representa um exemplo de implementacao do comando delete.
[4] permita a remocao logica de r
egistros de tres arquivos de dados de entrada, baseado na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos. a implementacao dessa funcionalidade deve ser realizada usando o conceito de fila (fifo) de registros

logicamente removidos, e deve seguir com flexibilidade a materia apresentada em sala de aula . os registros a serem removidos devem ser aqueles que satisfaçam qualquer um dos criterios de busca (logica or) determinados pelo usuario, sendo que a busca

 deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de remocao . ao se remover um registro, os valores dos bytes referentes aos campos ja armazenados no registro devem ser so

brescritos pelo caractere '#', com exceção dos valores dos campos relacionados ao tratamento da lista encadeada . a funcionalidade [4] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito,

ou seja, caso a solicitacao do usuario nao retorne nenhum registro a ser removido, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionat

ela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo inst
ituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [4]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 4
m1 nomecampo valorcampo1 m2 nomecampo valorcampo1 mn nomecam
po valorcampo nomecampomi valorcampomi nomecampom2 valorcampom2 nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho

pratico introdutorio . as remocoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de remocoes a serem realizadas . m e a quantidade de vezes que o par nome do campo e valor do campo pode repeti

r na busca pelos registros a serem removidos . o identificador da funcionalidade '4' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre o nome do campo e o valor do campo . os valores dos campos do

 tipo string devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
men
sagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 4 1 nomeestacao 'luz' 2 nomelinha 'verde'; codproxest 27
execucao da funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as remocoes.
usar a funcao binarionatela antes de iniciar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando insert into e usado para inserir dados em uma tabela . para tanto, devem ser especificados os valores a ser

em armazenados em cada coluna da tabela, de acordo com o tipo de dado definido . a funcionalidade [5] representa um exemplo de implementacao do comando insert into.
[5] permita a insercao de novos registros em tres arquivos de dados de entrada, basea

do na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e inserindo novos dados obrigatoriamente no final do arquivo, segui

ndo com flexibilidade a materia apresentada em sala de aula . o lixo que permanece no registro deve ser identificado pelo caractere '#' . na entrada da funcionalidade [5], os dados sao referentes aos seguintes campos, na ordem inversa: codestintegra,

 codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao.
campos com valores nulos, na entrada da funcionalidade, devem ser identificados com void ou empty . os valores dos campos do tipo string devem ser especi

ficados entre aspas simples (') . para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . a funcionalidade [5] deve ser executada n vezes seguidas . antes

de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são c

arlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [5]:
arquivosaida1.bin arquivosaida2.bin arq
uivosaida3.bin n 5
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao nomelinha codlinha, nomeestacao, codestacao
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao, nomelinha codlinha, nomeestacao, codestacao
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdutorio. as insercoes a serem realizadas nessa funcionalidade devem ser feitas obrig

atoriamente no final de cada um desses arquivos, desprezando qualquer espaco logicamente removido.
n e o numero de insercoes a serem realizadas. para cada insercao, deve ser informado os valores a serem inseridos nos arquivos, considerando os seguint

es campos, na ordem inversa: codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao. o identificador da funcionalidade '5' deve ser inserido ao final da primeira linha de comando.
valores nulos d

evem ser identificados, na entrada da funcionalidade, por void ou empty. cada uma das n insercoes deve ser especificada em uma linha diferente. deve ser deixado um ponto e virgula (;) entre os valores dos campos. os valores dos campos do tipo string

devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
mensagem de said
a caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 5 void; void; void; void; 'branca'; 10; 'teste'; 500 void; void; void; void; 'branca'; 10; 'nova estacao'; 501
 funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as insercoes.
usar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando update e usado para atualizar dados em uma tabela . para tanto, devem ser esp

ecificados quais valores de dados de quais campos devem ser atualizados, de acordo com algum criterio de busca dos registros a serem atualizados.
update tabela (ou seja, arquivo que contem os dados) set quais colunas e quais valores (ou seja, quais c

ampos e seus valores) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [6] representa um exemplo de implementacao do comando update.
[6] permita a atualizacao de registros de tres arquivos de dados de entrada, baseado na aborda

gem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e deve seguir com flexibilidade a materia apresentada em sala de aula . desde q

ue os registros do arquivo de dados sao de tamanho variavel (com limite de 120 bytes), se a atualizacao resultar em um registro maior que o espaco original, o registro atual deve ser marcado como removido e a nova versao deve ser inserida obrigatoria

mente no final do arquivo . o lixo que porventura permanecer no registro atualizado deve ser identificado pelo caractere '#'.
os registros a serem atualizados devem ser aqueles que satisfacam qualquer um dos criterios de busca (logica or) determinado

s pelo usuario, sendo que a busca deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de atualizacao . adicionalmente, o campo utilizado como busca nao precisa ser, necessaria

mente, o campo a ser atualizado . por exemplo, pode-se buscar pelo campo codestacao, e pode-se atualizar o campo nomelinha . campos a serem atualizados com valores nulos devem ser identificados, na entrada da funcionalidade, com void ou empty . a fun

cionalidade [6] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcio

nalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasi

l www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [6]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 6
b; valorcampob1; nomecampobmi; valorcampobm1 pl nomecampoa; valorcampoa nomecampoap1; valorcampoapi m2 nomecampob2; valorcampob2 nomecampobm2; valorcampobm2 p2 nomecampoa; valorcampoa nomecampoap2; valorcampoap2 mn nomecampobn; valorcampob nomecampob
ml nomecampo

mn; valorcampobmn pn nomecampoa; valorcampoan nomecampoapn; valorcampoapn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdu

torio . as atualizacoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de atualizacoes a serem realizadas . m e a quantidade de vezes que o par nomecampob (campo de busca) e valorcampob (valor

de busca) pode repetir para filtrar os registros, utilizando a logica or . deve ser deixado um ponto e virgula (;) entre nomecampob e valorcampob . os valores dos campos do tipo string devem ser especificados entre aspas simples (') . p e a quantidad

e de vezes que o par nomecampoa (campo a ser atualizado) e valorcampoa (novo valor) pode repetir . deve ser deixado um ponto e virgula (;) entre nomecampoa e valorcampoa . os valores das strings a serem atualizadas devem estar entre aspas simples (')

 . o identificador da funcionalidade '6' deve ser inserido ao final da primeira linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de inici

ar a execucao da funcionalidade.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
linhaintegra; 4; codestacaointegra; 55 1 codestacao; 15 1 nomeestacao; 'exemplo'
./executorprojeto est1.bin est2.bin est3.bin 2 6 2 codestacao; 1; nomeestacao; 'tucuruvi' 3 codproxestacao; 15; cod
usar a funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados f

rente as atualizacoes.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
restricoes
guintes restricoes tem que ser garantidas no desenvolvimento do trabalho:
as se
[1] o arquivo de dados deve ser gravado em disco no modo binario . o modo texto nao pode ser usado.
[2] os dados do registro descrevem os nomes dos campos, os quais nao podem s

er alterados . ademais, todos os campos devem estar presentes na implementacao, e nenhum campo adicional pode ser incluido . o tamanho e a ordem de cada campo deve obrigatoriamente seguir a nova especificacao proposta.
[3] deve haver a manipulacao de

 valores nulos, utilizando obrigatoriamente as strings "void" e "empty" e o valor numerico 0, conforme as instrucoes definidas.
[4] e necessario realizar o tratamento de truncamento de dados caso o registro atualizado exceda o limite de 120 bytes.
[5

] devem ser exibidos avisos ou mensagens de erro de acordo com a especificacao flexivel de cada funcionalidade.
[6] os dados devem ser obrigatoriamente escritos registro a registro (utilizando structs completas) . ou seja, nao e possivel escrever os

dados campo a campo . essa restricao refere-se a entrada/saida, ou seja, a forma como os dados sao escritos no arquivo.
[7] o(s) aluno(s) que desenvolveu(desenvolveram) o trabalho pratico deve(m) constar como comentario no inicio do codigo (i.e. nusp

 e nome do aluno) . para trabalhos desenvolvidos por mais do que um aluno, nao sera atribuida nota ao aluno cujos dados nao constarem no codigo fonte.
[8] todo codigo fonte deve ser documentado utilizando o padrao doxygen . a documentacao interna inc

lui a documentacao de procedimentos, de funcoes, de variaveis, de partes do codigo fonte que realizam tarefas especificas . ou seja, o codigo fonte deve ser documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais.
[9] r

estrição extra: o programa deve implementar um sistema de log que registre cada operacao de escrita realizada nos arquivos binarios em um arquivo de texto separado chamado "operacoes.log".
[10] restrição extra: o uso de memoria ram deve ser otimizado

 para que o programa nunca mantenha mais de 100 registros carregados simultaneamente, utilizando tecnicas de busca em disco (fseek).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao
paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais. [11] restrição extra: todos os ponteiros utilizados para manipulaca

o de arquivos e memoria devem ser validados imediatamente apos a declaracao, garantindo que nao haja vazamento de memoria (memory leaks) sob pena de desconsideracao da funcionalidade. [12] restrição extra: o programa deve ser capaz de lidar com inter

rupcoes de sinal (como ctrl+c), garantindo que os arquivos sejam fechados e o status de consistencia seja atualizado para '1' (inconsistente) antes da finalizacao forcada. [9] a implementacao deve ser realizada usando a linguagem de programação c . a

s funções das bibliotecas <stdio.h> devem ser utilizadas para operações relacionadas à escrita e leitura dos arquivos . a implementação não pode ser feita em qualquer outra linguagem de programação . o programa executará no [run.codes]. fundamentação

 teórica conceitos e características dos diversos métodos para representar os conceitos de campo e de registro em um arquivo de dados podem ser encontrados nos slides de sala de aula e também no livro file structures (second edition), de michael j. f

olk e bill zoellick. material para entregar arquivo compactado (a ser entregue no run.codes). deve ser preparado um arquivo.tar.gz (em vez de .zip) contendo: · código fonte do programa devidamente documentado com doxygen. · arquivo de configuracao do

 doxygen (doxyfile). vídeo (a ser entregue no e-disciplinas). um vídeo gravado pelos integrantes do grupo, o qual deve ter, no máximo, 3 minutos de gravação (em vez de 5) . o vídeo deve explicar o trabalho desenvolvido . ou seja, o grupo deve apresen

tar: cada funcionalidade e uma breve descrição de como a funcionalidade foi implementada . todos os integrantes do grupo devem participar do video, sendo que o tempo de apresentação dos integrantes deve ser balanceado . ou seja, o tempo de participaç

ão de cada integrante deve ser aproximadamente o mesmo . o uso da webcam é opcional (em vez de obrigatorio).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de cienci

as matematicas e de computacao departamento de ciencias de computacao
instrucoes para fazer o script de compilacao. no [run.codes], em vez de utilizar um makefile tradicional, voce deve fornecer um script em shell chamado "build.sh" . a diretiva prin

cipal deve garantir que a compilacao otimize o codigo para execucao em sistemas de 64 bits . adicionalmente, para utilizar a funcao binarionatela, e necessario utilizar a flag -static para garantir que todas as dependencias sejam incluidas no binario

 final.
assim, a forma mais simples de se fazer o script de automacao e:
#!/bin/bash gcc -o executorprojeto *.c -static -lm ./executorprojeto
lembrando que o uso de *.c e obrigatorio para incluir todos os modulos desenvolvidos . adicionalmente, certi
fique-se de que o arquivo build.sh tenha permissoes de execucao (chmod +x), caso contrario o ambiente de correcao manual nao conseguira iniciar os testes.
instrucoes de entrega. o programa deve ser submetido via [run.codes]: · pagina: https://runcode

s.icmc.usp.br/ · segunda feira: codigo de matricula: ALFA9 · terca feira: codigo de matricula: BETA2
o video gravado deve ser submetido por meio de um servico de nuvem (google drive ou dropbox) e o link deve ser enviado via e-disciplinas, no qual o g

rupo vai informar o nome de cada integrante, o numero do grupo e o link de acesso . ao submeter o link, certifique-se de que as permissoes de visualizacao estao abertas para "qualquer pessoa com o link" . links que exigirem solicitacao de acesso ou q

ue apresentarem erro de 404 receberao nota zero imediatamente.
criterio de correcao criterio de avaliacao do trabalho. na correcao do trabalho, serao ponderados os seguintes aspectos.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
· corretude da execucao do programa. · atendimento as novas especificacoes do registro de cabecalho de 2
5 bytes e dos registros de dados variaveis de ate 120 bytes. · atendimento as especificacoes da sintaxe flexivel dos comandos de cada funcionalidade e do formato de saida com delimitadores pipe (|). · qualidade da documentacao doxygen entregue. a doc

umentacao interna tera um peso consideravel no trabalho. · estruturacao da solucao. o projeto deve apresentar uma organizacao adequada de arquivos e diretorios. · centralizacao do codigo. trechos de codigo que aparecem repetidamente podem ser mantido

s de forma linear para evitar a fragmentacao por excesso de funcoes. · uso de ferramentas de inteligencia artificial. o uso dessas ferramentas e permitido exclusivamente para a geracao de casos de teste e documentacao, mas proibido para a logica das

funcionalidades . o uso indevido acarretara desconto rigoroso na nota. video. integrantes que nao participarem da apresentacao receberao nota 0 no trabalho correspondente. casos de teste no [run.codes]. juntamente com a especificacao do trabalho, ser

UNIVERSIDADE DE SÃO PAULO
INSTITUTO DE CIÊNCIAS MATEMÁTICAS E DE COMPUTAÇÃO
Departamento de Ciências de Computação
Disciplina de Organização de Arquivos (SCC0215)
antos Pires · gustavo.rspires@usp.br ou telegram: @darrocaxd
Docente Profa. Dra. Cristina Dutra de Aguiar cdac@icmc.usp.br
João Gabriel Pieroli da Silva · joagabrielpieroli@usp.br ou telegram: @bielcomp24
Monitores
Pedro Lunkes Villela · pedrolunkesvillela@usp.br ou telegram: @pedrolunkes
Gustavo Ramos S
Renan Banci Catarin · renanbcata
rin@usp.br ou telegram: @Reckat
Renan Trofino Silva · renan.trofino@usp.br ou telegram: @renan823
Vinícius Souza Freitas · vininicius@usp.br ou telegram: @Vininicius
Trabalho Introdutório
ntrada e gerar um arquivo binário com esses dados, bem como realizar operações de busca, remoção e atualização. Ele é um trabalho introdutório, de forma que será usado como base para o desenvolvimento de todos os demais trabalhos da disciplina.
Este trabalho tem como objetivo obter dados de um arquivo de e
O tra

balho deve ser feito individualmente ou em trios (3 alunos) da mesma turma. A solução deve ser proposta exclusivamente pelos alunos com base nos conhecimentos adquiridos nas aulas. Consulte as notas de aula e o livro texto quando necessário.
Fundamen

tos da disciplina de Bases de Dados
A disciplina de Organização de Arquivos é uma disciplina fundamental para a disciplina de Bases de Dados. A definição dos trabalhos práticos é feita considerando esse aspecto, ou seja, os trabalhos são especificado

s em termos de várias funcionalidades, e essas funcionalidades são relacionadas tanto com desafios enfrentados no mercado de trabalho quanto com as funcionalidades da linguagem SQL (Structured Query Language), que é a linguagem utilizada por sistemas

 gerenciadores.
Av. Trabalhador São-carlense, 400 centro. São Carlos - SP cep 13566-590. Brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao de banco de dados (sgbd

s) relacionais. as caracteristicas e o detalhamento de sql serao aprendidos na disciplina de bases de dados . porem, por meio do desenvolvimento deste trabalho pratico, os alunos podem entrar em contato com alguns comandos da linguagem sql e verifica

r como eles sao implementados . os trabalhos práticos têm como objetivo armazenar e recuperar dados relacionados às estações e linhas do metrô e da cptm (companhia paulista de trens metropolitanos) da região metropolitana da cidade de são paulo (sp)

. um exemplo de uso desses dados é: "eu preciso pegar uma linha de metrô para ir para o aeroporto de guarulhos" . os dados manipulados indicam o trajeto que deve ser feito . em detalhes, os dados se referem às estações, às linhas, às distâncias entre

 as estações e aos trajetos . na disciplina de bases de dados, é ensinado que esses dados devem ser armazenados em arquivos separados, respeitando a normalização . entretanto, para aumentar a complexidade de gerencimento da redundancia nos trabalhos

da disciplina de organização de arquivos, todos os dados serão armazenados em tres arquivos distintos . isso significa que existe redundância dos dados, ou seja, o mesmo valor de dados é armazenado mais do que uma vez . descrição do arquivo de dados

. um arquivo de dados possui um registro de cabeçalho e 0 ou mais registros de dados . a descrição do registro de cabeçalho é feita conforme a definição a seguir . registro de cabeçalho. o registro de cabeçalho deve conter os seguintes campos: · stat

us: indica a consistência do arquivo de dados, devido à queda de energia, travamento do programa, etc. pode assumir os valores '1', para indicar que o arquivo de dados está inconsistente, ou '0', para indicar que o arquivo de dados está consistente .

 ao se abrir um arquivo para escrita, seu status deve ser '1' e, ao finalizar o uso desse arquivo, seu status deve ser '0' - tamanho: string de 1 byte. · topo: armazena o byte offset de um registro logicamente removido, ou 0 caso não haja registros l

ogicamente removidos - tamanho: inteiro de 4 bytes . av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias

 de computacao · proxrrn: armazena o valor do proximo rrn disponivel. deve ser iniciado com o valor '1' e deve ser alterado sempre que necessario tamanho: inteiro de 4 bytes. · nroestacoes: indica a quantidade de estacoes diferentes que estao armazen

adas no arquivo de dados . note que, se duas ou mais estacoes têm o mesmo nome, elas sao consideradas estacoes distintas - tamanho: inteiro de 4 bytes. · nroparesestacao: indica a quantidade de pares (codestacao, codproxestacao) diferentes que estao

armazenados no arquivo de dados tamanho: inteiro de 4 bytes. representacao grafica do registro de cabecalho. o tamanho do registro de cabecalho deve ser de 25 bytes, representado da seguinte forma: "0", "1", "2 3 4 5", "6 7 8 9", "10 11 12 13", "14 1

5 16 17 18 19 20 21", "22 23 24" "status", , "topo", , "proxrrn", , "nroestacoes", , "nro pares estacao" observacoes importantes. · o registro de cabecalho deve seguir estritamente a ordem definida na sua representacao grafica. · os campos sao de tam

anho variavel com delimitadores. portanto, os valores que forem armazenados devem ser finalizados por '|'. · neste projeto, o conceito de pagina de disco deve ser obrigatoriamente considerado para o calculo de offsets. registros de dados. os registro

s de dados sao de tamanho variavel, com campos de tamanho fixo e campos de tamanho variavel . para os campos de tamanho variavel, deve ser usado o metodo de delimitador de campo . os campos de tamanho fixo sao definidos da seguinte forma: · codestaca

o: codigo da estacao - inteiro - tamanho: 4 bytes. · codlinha: codigo da linha - inteiro - tamanho: 4 bytes. · codproxestacao: codigo da proxima estacao - inteiro - tamanho: 4 bytes. · distproxestacao: distancia para a proxima estacao - inteiro - tam

anho: 4 bytes. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp sao carlos scc universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao

 codlinhaintegra: codigo da linha que faz a integracao entre as linhas inteiro tamanho: 8 bytes · codestintegra: codigo da estacao que faz a integracao entre as linhas - inteiro tamanho: 8 bytes os campos de tamanho variavel sao definidos da seguinte

 forma: · nomeestacao: nome da estacao nomelinha: nome da linha adicionalmente, os seguintes campos de tamanho fixo tambem compoem cada registro. esses campos sao necessarios para o gerenciamento de registros logicamente removidos e para oferecer sup

orte para o metodo de delimitadores de campo. removido: indica se o registro esta logicamente removido. pode assumir os valores '0', para indicar que o registro esta marcado como logicamente removido, ou '1', para indicar que o registro nao esta marc

ado como removido. tamanho: string de 1 byte. proximo: armazena o byte offset do proximo registro logicamente removido tamanho: inteiro de 8 bytes. deve ser inicializado com o valor 0 quando necessario. os dados sao fornecidos juntamente com a especi

ficacao deste trabalho pratico por meio de um arquivo .json, sendo que sua especificacao esta disponivel na pagina da disciplina. no arquivo .json, o separador de campos e a chave do objeto e o primeiro registro nao especifica metadados. adicionalmen

te, campos nulos sao representados pela string "empty". representacao grafica dos registros de dados. o tamanho dos registros de dados deve ser variavel, com um limite maximo de 120 bytes, representado da seguinte forma: av. trabalhador são-carlense,

 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp 88 são carlos scc universidade de são paulo instituto de ciências matemáticas e de computação departamento de ciências de computação
representação gráfica dos registros de d
ados. o tamanho dos registros de dados deve ser variável até 120 bytes, representado da seguinte forma:
"0", "1", "9 10 11 12 13 14 15 16", "17 18 19 20", "21 22 23 24", "25 26 27 28" "removido", , "próximo (offset)", , "codestacao", , "codlinha", ,

"codproxestacao"
"29 30 31 32", "33 34 35 36 37 38 39 40", "41 42 43 44 45 46 47 48", "49...", "...119" "distproxestacao", , "codlinhaintegra", , "codestintegra", , "nomeestacao|", , "nomelinha|"
observações importantes. · cada registro de dados deve

 seguir estritamente a ordem definida na sua representação gráfica. · as strings de tamanho variável são identificadas por um delimitador pipe (|) e, portanto, devem ser finalizadas com este caractere. · os campos codestacao e nomeestacao aceitam val

ores nulos. os demais campos são de preenchimento obrigatório e não aceitam valores nulos. o arquivo .json com os dados de entrada já garante essa característica. · para os campos de tamanho fixo, os valores nulos devem ser representados pelo valor 0

. · para os campos de tamanho variável, armazenar um valor nulo significa armazenar a string "empty" seguida do delimitador. · deve ser feita a diferenciação entre o espaço utilizado e o lixo. sempre que houver lixo, ele deve ser identificado pelo ca

ractere '#'. nenhum byte do registro deve permanecer vazio, ou seja, cada byte deve armazenar um valor válido ou '#'. · não existe a necessidade de truncamento dos dados. o arquivo .json com os dados de entrada já garante essa característica. · neste

 projeto, o conceito de página de disco deve ser obrigatoriamente considerado.
programa descrição geral. implemente um programa em c por meio do qual o usuário possa obter dados de um arquivo de entrada e gerar arquivos binários com esses dados, bem

como realizar operações de busca nesses arquivos binários.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ci
encias de computacao importante. a definicao da sintaxe de cada comando bem como sua saida devem seguir com flexibilidade as especificacoes definidas em cada funcionalidade, desde que a logica de negocio seja mantida . para especificar a sintaxe de e

xecucucao, considere que o programa seja chamado de "executorprojeto" . essas orientacoes devem ser seguidas com cautela, uma vez que a avaliacao do funcionamento do programa sera realizada de forma manual pelos monitores . de forma geral, a ultima e

ntrada da entrada padrao e sempre o identificador de suas funcionalidades, conforme especificado a seguir . centralizacao. e importante manter o codigo em blocos extensos para evitar a fragmentacao excessiva do programa. trechos de programa que apare

cerem varias vezes podem ser repetidos para facilitar a leitura linear do fluxo . descricao especifica. o programa deve oferecer as seguintes funcionalidades : na linguagem sql, o comando create table e usado para criar uma tabela, a qual e implement

ada como um arquivo . geralmente, uma tabela possui um nome (que corresponde ao nome do arquivo) e varias colunas, as quais correspondem aos campos dos registros do arquivo de dados . a funcionalidade [1] representa um exemplo de implementacao do com

ando create table. [1] permita a leitura de varios registros obtidos a partir de um arquivo de entrada no formato json e a gravacao desses registros em tres arquivos de dados de saida . o arquivo de entrada no formato json e fornecido juntamente com

a especificacao do projeto, enquanto os arquivos de dados de saida devem ser gerados de acordo com as novas especificacoes deste trabalho pratico . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibiliz

ada na pagina do projeto da disciplina, para validar a integridade previa do ambiente . a funcao binarionatela deve ser usada antes que o arquivo seja aberto para escrita. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. bras

il www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [1]:
3.bin 1
arquivoentrada.json arquivosaida1.bin arquivosaida2.bin arquivosaida
onde:
arquivoentrada.json e um arquivo .json que contem os valores dos campos dos registros a serem armazenados nos arquivos binarios . arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios gerados conforme as nova

s especificacoes descritas neste trabalho pratico. 1 e o identificador da funcionalidade, agora inserido ao final da linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de saida no formato binario usando a funcao f

ornecida binarionatela antes de abrir os arquivos para escrita.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
ela antes de iniciar a funcionalidade, para validar a integridade previa do ambiente.
./executorprojeto estacao.json est1.bin est2.bin est3.bin 1
na linguagem sql, o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select. o comando mais basico consist
usar a funcao binarionat

e em especificar as clausulas select e from, da seguinte forma:
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos)
a funcionalidade [2] representa um exemplo de implementacao do

comando select . como todos os registros devem ser recuperados nessa funcionalidade, sua implementacao consiste em percorrer o arquivo de tras para frente (do ultimo registro para o primeiro).
[2] permita a recuperacao dos dados de todos os registros

 armazenados nos tres arquivos de dados de entrada, mostrando os dados de forma desorganizada e aleatoria na saida padrao para dificultar a leitura automatizada . o tratamento de 'lixo' deve ser ignorado, exibindo os caracteres '#' conforme aparecem

no disco . registros marcados como logicamente removidos (valor '0') devem ser exibidos com destaque.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias mat
ematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [2]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin 2
onde:
rios gerados conforme as especificacoes descritas neste trabalho pratico.
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos bina
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem ser mostrados de forma sequencial separados por um p

ipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos da seguinte forma: ao inves de exibir o valor 0, escreva VOID . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos da seguinte forma: EMPTY . a ordem

 de exibicao dos campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao existam registros:

arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
l 1 Parada Inglesa 2
exemplo de execucao (e mostrado um exemplo ilustrativo):
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bin 2 NULO NULO 992 2 Azul 1 Tucuruvi 1 55 4 1057 3 Azu
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
conforme visto na
 funcionalidade [2], na linguagem sql o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select . alem das clausulas select e from, outra clausula muito comum e a clausula where, que permite q

ue seja definido um criterio de busca sobre um ou mais campos, o qual e nomeado como criterio de selecao.
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos) where criterio de sel

ecao (ou seja, criterio de busca)
a funcionalidade [3] representa um exemplo de implementacao do comando select considerando a clausula where . como não existe indice definido sobre os campos dos registros, a implementacao dessa funcionalidade consis

te em percorrer o arquivo de tras para frente (da ultima pagina para a primeira).
[3] permita a recuperacao dos dados de todos os registros dos tres arquivos de dados de entrada, de forma que esses registros satisfacam qualquer um dos criterios de bu

sca (logica or) determinados pelo usuario . qualquer campo pode ser utilizado como forma de busca . adicionalmente, a busca deve ser feita considerando um ou mais campos . por exemplo, e possivel realizar a busca considerando somente o campo codestac

ao ou considerando os campos nomeestacao e nomelinha.
esta funcionalidade pode retornar 0 registros (quando nenhum satisfaz ao criterio de busca), 1 registro (quando apenas um satisfaz ao criterio de busca), ou varios registros . os valores dos campo

s do tipo string devem ser especificados entre aspas simples ('). para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . para a busca por valores nulos, d

eve-se especificar o valor void ou empty . registros marcados como logicamente removidos (status '0') devem ser exibidos obrigatoriamente . os tres arquivos de dados de entrada devem ser percorridos simultaneamente de forma decrescente.
av. trabalhad

or são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
sintaxe do comando para a funcionalidade [3]:
arquiv
osaida1.bin arquivosaida2.bin arquivosaida3.bin n 3
m1 nomecampo valorcampo1 nomecampomi valorcampoml m2 nomecampo valorcampo1 nomecampom2 valorcampom2 mn nomecampo valorcampo nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arqu
ivosaida3.bin sao os arquivos binarios de um determinado tipo, os quais foram gerados conforme as novas especificacoes descritas neste trabalho pratico . n e a quantidade de vezes que a busca deve acontecer . m e a quantidade de vezes que o par nome

do campo e valor do campo pode repetir em uma busca . o identificador da funcionalidade '3' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre nomecampo e valorcampo . os valores dos campos do tipo

 string devem ser especificados entre aspas simples (') . buscas por valores nulos devem ser especificadas com void ou empty.
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem

ser mostrados de forma sequencial separados por um pipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos como void . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos como empty . a ordem de exibicao d

os campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao seja encontrado o registro que c

ontem o valor do campo ou o campo pertence a um registro que esteja ativo (nao removido):
arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
n 1 3 1 nomeestacao 'luz' nulo nulo nulo 112 7 rubi luz 111 19 1257 56 4 amarela luz 55 55 4 nulo 10 1 azul luz 9
exemplo de execucao:
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bi
universidade de sao paulo instituto de

ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando delete e usado para remover dados em uma tabela . para tanto, devem ser especificados quais dados (ou seja, registros) devem ser removidos, de aco

rdo com algum criterio.
delete from tabela (ou seja, arquivo que contem os campos) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [4] representa um exemplo de implementacao do comando delete.
[4] permita a remocao logica de r
egistros de tres arquivos de dados de entrada, baseado na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos. a implementacao dessa funcionalidade deve ser realizada usando o conceito de fila (fifo) de registros

logicamente removidos, e deve seguir com flexibilidade a materia apresentada em sala de aula . os registros a serem removidos devem ser aqueles que satisfaçam qualquer um dos criterios de busca (logica or) determinados pelo usuario, sendo que a busca

 deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de remocao . ao se remover um registro, os valores dos bytes referentes aos campos ja armazenados no registro devem ser so

brescritos pelo caractere '#', com exceção dos valores dos campos relacionados ao tratamento da lista encadeada . a funcionalidade [4] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito,

ou seja, caso a solicitacao do usuario nao retorne nenhum registro a ser removido, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionat

ela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo inst
ituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [4]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 4
m1 nomecampo valorcampo1 m2 nomecampo valorcampo1 mn nomecam
po valorcampo nomecampomi valorcampomi nomecampom2 valorcampom2 nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho

pratico introdutorio . as remocoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de remocoes a serem realizadas . m e a quantidade de vezes que o par nome do campo e valor do campo pode repeti

r na busca pelos registros a serem removidos . o identificador da funcionalidade '4' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre o nome do campo e o valor do campo . os valores dos campos do

 tipo string devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
men
sagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 4 1 nomeestacao 'luz' 2 nomelinha 'verde'; codproxest 27
execucao da funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as remocoes.
usar a funcao binarionatela antes de iniciar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando insert into e usado para inserir dados em uma tabela . para tanto, devem ser especificados os valores a ser

em armazenados em cada coluna da tabela, de acordo com o tipo de dado definido . a funcionalidade [5] representa um exemplo de implementacao do comando insert into.
[5] permita a insercao de novos registros em tres arquivos de dados de entrada, basea

do na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e inserindo novos dados obrigatoriamente no final do arquivo, segui

ndo com flexibilidade a materia apresentada em sala de aula . o lixo que permanece no registro deve ser identificado pelo caractere '#' . na entrada da funcionalidade [5], os dados sao referentes aos seguintes campos, na ordem inversa: codestintegra,

 codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao.
campos com valores nulos, na entrada da funcionalidade, devem ser identificados com void ou empty . os valores dos campos do tipo string devem ser especi

ficados entre aspas simples (') . para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . a funcionalidade [5] deve ser executada n vezes seguidas . antes

de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são c

arlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [5]:
arquivosaida1.bin arquivosaida2.bin arq
uivosaida3.bin n 5
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao nomelinha codlinha, nomeestacao, codestacao
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao, nomelinha codlinha, nomeestacao, codestacao
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdutorio. as insercoes a serem realizadas nessa funcionalidade devem ser feitas obrig

atoriamente no final de cada um desses arquivos, desprezando qualquer espaco logicamente removido.
n e o numero de insercoes a serem realizadas. para cada insercao, deve ser informado os valores a serem inseridos nos arquivos, considerando os seguint

es campos, na ordem inversa: codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao. o identificador da funcionalidade '5' deve ser inserido ao final da primeira linha de comando.
valores nulos d

evem ser identificados, na entrada da funcionalidade, por void ou empty. cada uma das n insercoes deve ser especificada em uma linha diferente. deve ser deixado um ponto e virgula (;) entre os valores dos campos. os valores dos campos do tipo string

devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
mensagem de said
a caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 5 void; void; void; void; 'branca'; 10; 'teste'; 500 void; void; void; void; 'branca'; 10; 'nova estacao'; 501
 funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as insercoes.
usar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando update e usado para atualizar dados em uma tabela . para tanto, devem ser esp

ecificados quais valores de dados de quais campos devem ser atualizados, de acordo com algum criterio de busca dos registros a serem atualizados.
update tabela (ou seja, arquivo que contem os dados) set quais colunas e quais valores (ou seja, quais c

ampos e seus valores) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [6] representa um exemplo de implementacao do comando update.
[6] permita a atualizacao de registros de tres arquivos de dados de entrada, baseado na aborda

gem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e deve seguir com flexibilidade a materia apresentada em sala de aula . desde q

ue os registros do arquivo de dados sao de tamanho variavel (com limite de 120 bytes), se a atualizacao resultar em um registro maior que o espaco original, o registro atual deve ser marcado como removido e a nova versao deve ser inserida obrigatoria

mente no final do arquivo . o lixo que porventura permanecer no registro atualizado deve ser identificado pelo caractere '#'.
os registros a serem atualizados devem ser aqueles que satisfacam qualquer um dos criterios de busca (logica or) determinado

s pelo usuario, sendo que a busca deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de atualizacao . adicionalmente, o campo utilizado como busca nao precisa ser, necessaria

mente, o campo a ser atualizado . por exemplo, pode-se buscar pelo campo codestacao, e pode-se atualizar o campo nomelinha . campos a serem atualizados com valores nulos devem ser identificados, na entrada da funcionalidade, com void ou empty . a fun

cionalidade [6] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcio

nalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasi

l www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [6]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 6
b; valorcampob1; nomecampobmi; valorcampobm1 pl nomecampoa; valorcampoa nomecampoap1; valorcampoapi m2 nomecampob2; valorcampob2 nomecampobm2; valorcampobm2 p2 nomecampoa; valorcampoa nomecampoap2; valorcampoap2 mn nomecampobn; valorcampob nomecampob
ml nomecampo

mn; valorcampobmn pn nomecampoa; valorcampoan nomecampoapn; valorcampoapn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdu

torio . as atualizacoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de atualizacoes a serem realizadas . m e a quantidade de vezes que o par nomecampob (campo de busca) e valorcampob (valor

de busca) pode repetir para filtrar os registros, utilizando a logica or . deve ser deixado um ponto e virgula (;) entre nomecampob e valorcampob . os valores dos campos do tipo string devem ser especificados entre aspas simples (') . p e a quantidad

e de vezes que o par nomecampoa (campo a ser atualizado) e valorcampoa (novo valor) pode repetir . deve ser deixado um ponto e virgula (;) entre nomecampoa e valorcampoa . os valores das strings a serem atualizadas devem estar entre aspas simples (')

 . o identificador da funcionalidade '6' deve ser inserido ao final da primeira linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de inici

ar a execucao da funcionalidade.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
linhaintegra; 4; codestacaointegra; 55 1 codestacao; 15 1 nomeestacao; 'exemplo'
./executorprojeto est1.bin est2.bin est3.bin 2 6 2 codestacao; 1; nomeestacao; 'tucuruvi' 3 codproxestacao; 15; cod
usar a funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados f

rente as atualizacoes.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
restricoes
guintes restricoes tem que ser garantidas no desenvolvimento do trabalho:
as se
[1] o arquivo de dados deve ser gravado em disco no modo binario . o modo texto nao pode ser usado.
[2] os dados do registro descrevem os nomes dos campos, os quais nao podem s

er alterados . ademais, todos os campos devem estar presentes na implementacao, e nenhum campo adicional pode ser incluido . o tamanho e a ordem de cada campo deve obrigatoriamente seguir a nova especificacao proposta.
[3] deve haver a manipulacao de

 valores nulos, utilizando obrigatoriamente as strings "void" e "empty" e o valor numerico 0, conforme as instrucoes definidas.
[4] e necessario realizar o tratamento de truncamento de dados caso o registro atualizado exceda o limite de 120 bytes.
[5

] devem ser exibidos avisos ou mensagens de erro de acordo com a especificacao flexivel de cada funcionalidade.
[6] os dados devem ser obrigatoriamente escritos registro a registro (utilizando structs completas) . ou seja, nao e possivel escrever os

dados campo a campo . essa restricao refere-se a entrada/saida, ou seja, a forma como os dados sao escritos no arquivo.
[7] o(s) aluno(s) que desenvolveu(desenvolveram) o trabalho pratico deve(m) constar como comentario no inicio do codigo (i.e. nusp

 e nome do aluno) . para trabalhos desenvolvidos por mais do que um aluno, nao sera atribuida nota ao aluno cujos dados nao constarem no codigo fonte.
[8] todo codigo fonte deve ser documentado utilizando o padrao doxygen . a documentacao interna inc

lui a documentacao de procedimentos, de funcoes, de variaveis, de partes do codigo fonte que realizam tarefas especificas . ou seja, o codigo fonte deve ser documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais.
[9] r

estrição extra: o programa deve implementar um sistema de log que registre cada operacao de escrita realizada nos arquivos binarios em um arquivo de texto separado chamado "operacoes.log".
[10] restrição extra: o uso de memoria ram deve ser otimizado

 para que o programa nunca mantenha mais de 100 registros carregados simultaneamente, utilizando tecnicas de busca em disco (fseek).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao
paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais. [11] restrição extra: todos os ponteiros utilizados para manipulaca

o de arquivos e memoria devem ser validados imediatamente apos a declaracao, garantindo que nao haja vazamento de memoria (memory leaks) sob pena de desconsideracao da funcionalidade. [12] restrição extra: o programa deve ser capaz de lidar com inter

rupcoes de sinal (como ctrl+c), garantindo que os arquivos sejam fechados e o status de consistencia seja atualizado para '1' (inconsistente) antes da finalizacao forcada. [9] a implementacao deve ser realizada usando a linguagem de programação c . a

s funções das bibliotecas <stdio.h> devem ser utilizadas para operações relacionadas à escrita e leitura dos arquivos . a implementação não pode ser feita em qualquer outra linguagem de programação . o programa executará no [run.codes]. fundamentação

 teórica conceitos e características dos diversos métodos para representar os conceitos de campo e de registro em um arquivo de dados podem ser encontrados nos slides de sala de aula e também no livro file structures (second edition), de michael j. f

olk e bill zoellick. material para entregar arquivo compactado (a ser entregue no run.codes). deve ser preparado um arquivo.tar.gz (em vez de .zip) contendo: · código fonte do programa devidamente documentado com doxygen. · arquivo de configuracao do

 doxygen (doxyfile). vídeo (a ser entregue no e-disciplinas). um vídeo gravado pelos integrantes do grupo, o qual deve ter, no máximo, 3 minutos de gravação (em vez de 5) . o vídeo deve explicar o trabalho desenvolvido . ou seja, o grupo deve apresen

tar: cada funcionalidade e uma breve descrição de como a funcionalidade foi implementada . todos os integrantes do grupo devem participar do video, sendo que o tempo de apresentação dos integrantes deve ser balanceado . ou seja, o tempo de participaç

ão de cada integrante deve ser aproximadamente o mesmo . o uso da webcam é opcional (em vez de obrigatorio).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de cienci

as matematicas e de computacao departamento de ciencias de computacao
instrucoes para fazer o script de compilacao. no [run.codes], em vez de utilizar um makefile tradicional, voce deve fornecer um script em shell chamado "build.sh" . a diretiva prin

cipal deve garantir que a compilacao otimize o codigo para execucao em sistemas de 64 bits . adicionalmente, para utilizar a funcao binarionatela, e necessario utilizar a flag -static para garantir que todas as dependencias sejam incluidas no binario

 final.
assim, a forma mais simples de se fazer o script de automacao e:
#!/bin/bash gcc -o executorprojeto *.c -static -lm ./executorprojeto
lembrando que o uso de *.c e obrigatorio para incluir todos os modulos desenvolvidos . adicionalmente, certi
fique-se de que o arquivo build.sh tenha permissoes de execucao (chmod +x), caso contrario o ambiente de correcao manual nao conseguira iniciar os testes.
instrucoes de entrega. o programa deve ser submetido via [run.codes]: · pagina: https://runcode

s.icmc.usp.br/ · segunda feira: codigo de matricula: ALFA9 · terca feira: codigo de matricula: BETA2
o video gravado deve ser submetido por meio de um servico de nuvem (google drive ou dropbox) e o link deve ser enviado via e-disciplinas, no qual o g

rupo vai informar o nome de cada integrante, o numero do grupo e o link de acesso . ao submeter o link, certifique-se de que as permissoes de visualizacao estao abertas para "qualquer pessoa com o link" . links que exigirem solicitacao de acesso ou q

ue apresentarem erro de 404 receberao nota zero imediatamente.
criterio de correcao criterio de avaliacao do trabalho. na correcao do trabalho, serao ponderados os seguintes aspectos.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
· corretude da execucao do programa. · atendimento as novas especificacoes do registro de cabecalho de 2
5 bytes e dos registros de dados variaveis de ate 120 bytes. · atendimento as especificacoes da sintaxe flexivel dos comandos de cada funcionalidade e do formato de saida com delimitadores pipe (|). · qualidade da documentacao doxygen entregue. a doc

umentacao interna tera um peso consideravel no trabalho. · estruturacao da solucao. o projeto deve apresentar uma organizacao adequada de arquivos e diretorios. · centralizacao do codigo. trechos de codigo que aparecem repetidamente podem ser mantido

s de forma linear para evitar a fragmentacao por excesso de funcoes. · uso de ferramentas de inteligencia artificial. o uso dessas ferramentas e permitido exclusivamente para a geracao de casos de teste e documentacao, mas proibido para a logica das

funcionalidades . o uso indevido acarretara desconto rigoroso na nota. video. integrantes que nao participarem da apresentacao receberao nota 0 no trabalho correspondente. casos de teste no [run.codes]. juntamente com a especificacao do trabalho, ser

UNIVERSIDADE DE SÃO PAULO
INSTITUTO DE CIÊNCIAS MATEMÁTICAS E DE COMPUTAÇÃO
Departamento de Ciências de Computação
Disciplina de Organização de Arquivos (SCC0215)
antos Pires · gustavo.rspires@usp.br ou telegram: @darrocaxd
Docente Profa. Dra. Cristina Dutra de Aguiar cdac@icmc.usp.br
João Gabriel Pieroli da Silva · joagabrielpieroli@usp.br ou telegram: @bielcomp24
Monitores
Pedro Lunkes Villela · pedrolunkesvillela@usp.br ou telegram: @pedrolunkes
Gustavo Ramos S
Renan Banci Catarin · renanbcata
rin@usp.br ou telegram: @Reckat
Renan Trofino Silva · renan.trofino@usp.br ou telegram: @renan823
Vinícius Souza Freitas · vininicius@usp.br ou telegram: @Vininicius
Trabalho Introdutório
ntrada e gerar um arquivo binário com esses dados, bem como realizar operações de busca, remoção e atualização. Ele é um trabalho introdutório, de forma que será usado como base para o desenvolvimento de todos os demais trabalhos da disciplina.
Este trabalho tem como objetivo obter dados de um arquivo de e
O tra

balho deve ser feito individualmente ou em trios (3 alunos) da mesma turma. A solução deve ser proposta exclusivamente pelos alunos com base nos conhecimentos adquiridos nas aulas. Consulte as notas de aula e o livro texto quando necessário.
Fundamen

tos da disciplina de Bases de Dados
A disciplina de Organização de Arquivos é uma disciplina fundamental para a disciplina de Bases de Dados. A definição dos trabalhos práticos é feita considerando esse aspecto, ou seja, os trabalhos são especificado

s em termos de várias funcionalidades, e essas funcionalidades são relacionadas tanto com desafios enfrentados no mercado de trabalho quanto com as funcionalidades da linguagem SQL (Structured Query Language), que é a linguagem utilizada por sistemas

 gerenciadores.
Av. Trabalhador São-carlense, 400 centro. São Carlos - SP cep 13566-590. Brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao de banco de dados (sgbd

s) relacionais. as caracteristicas e o detalhamento de sql serao aprendidos na disciplina de bases de dados . porem, por meio do desenvolvimento deste trabalho pratico, os alunos podem entrar em contato com alguns comandos da linguagem sql e verifica

r como eles sao implementados . os trabalhos práticos têm como objetivo armazenar e recuperar dados relacionados às estações e linhas do metrô e da cptm (companhia paulista de trens metropolitanos) da região metropolitana da cidade de são paulo (sp)

. um exemplo de uso desses dados é: "eu preciso pegar uma linha de metrô para ir para o aeroporto de guarulhos" . os dados manipulados indicam o trajeto que deve ser feito . em detalhes, os dados se referem às estações, às linhas, às distâncias entre

 as estações e aos trajetos . na disciplina de bases de dados, é ensinado que esses dados devem ser armazenados em arquivos separados, respeitando a normalização . entretanto, para aumentar a complexidade de gerencimento da redundancia nos trabalhos

da disciplina de organização de arquivos, todos os dados serão armazenados em tres arquivos distintos . isso significa que existe redundância dos dados, ou seja, o mesmo valor de dados é armazenado mais do que uma vez . descrição do arquivo de dados

. um arquivo de dados possui um registro de cabeçalho e 0 ou mais registros de dados . a descrição do registro de cabeçalho é feita conforme a definição a seguir . registro de cabeçalho. o registro de cabeçalho deve conter os seguintes campos: · stat

us: indica a consistência do arquivo de dados, devido à queda de energia, travamento do programa, etc. pode assumir os valores '1', para indicar que o arquivo de dados está inconsistente, ou '0', para indicar que o arquivo de dados está consistente .

 ao se abrir um arquivo para escrita, seu status deve ser '1' e, ao finalizar o uso desse arquivo, seu status deve ser '0' - tamanho: string de 1 byte. · topo: armazena o byte offset de um registro logicamente removido, ou 0 caso não haja registros l

ogicamente removidos - tamanho: inteiro de 4 bytes . av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias

 de computacao · proxrrn: armazena o valor do proximo rrn disponivel. deve ser iniciado com o valor '1' e deve ser alterado sempre que necessario tamanho: inteiro de 4 bytes. · nroestacoes: indica a quantidade de estacoes diferentes que estao armazen

adas no arquivo de dados . note que, se duas ou mais estacoes têm o mesmo nome, elas sao consideradas estacoes distintas - tamanho: inteiro de 4 bytes. · nroparesestacao: indica a quantidade de pares (codestacao, codproxestacao) diferentes que estao

armazenados no arquivo de dados tamanho: inteiro de 4 bytes. representacao grafica do registro de cabecalho. o tamanho do registro de cabecalho deve ser de 25 bytes, representado da seguinte forma: "0", "1", "2 3 4 5", "6 7 8 9", "10 11 12 13", "14 1

5 16 17 18 19 20 21", "22 23 24" "status", , "topo", , "proxrrn", , "nroestacoes", , "nro pares estacao" observacoes importantes. · o registro de cabecalho deve seguir estritamente a ordem definida na sua representacao grafica. · os campos sao de tam

anho variavel com delimitadores. portanto, os valores que forem armazenados devem ser finalizados por '|'. · neste projeto, o conceito de pagina de disco deve ser obrigatoriamente considerado para o calculo de offsets. registros de dados. os registro

s de dados sao de tamanho variavel, com campos de tamanho fixo e campos de tamanho variavel . para os campos de tamanho variavel, deve ser usado o metodo de delimitador de campo . os campos de tamanho fixo sao definidos da seguinte forma: · codestaca

o: codigo da estacao - inteiro - tamanho: 4 bytes. · codlinha: codigo da linha - inteiro - tamanho: 4 bytes. · codproxestacao: codigo da proxima estacao - inteiro - tamanho: 4 bytes. · distproxestacao: distancia para a proxima estacao - inteiro - tam

anho: 4 bytes. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp sao carlos scc universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao

 codlinhaintegra: codigo da linha que faz a integracao entre as linhas inteiro tamanho: 8 bytes · codestintegra: codigo da estacao que faz a integracao entre as linhas - inteiro tamanho: 8 bytes os campos de tamanho variavel sao definidos da seguinte

 forma: · nomeestacao: nome da estacao nomelinha: nome da linha adicionalmente, os seguintes campos de tamanho fixo tambem compoem cada registro. esses campos sao necessarios para o gerenciamento de registros logicamente removidos e para oferecer sup

orte para o metodo de delimitadores de campo. removido: indica se o registro esta logicamente removido. pode assumir os valores '0', para indicar que o registro esta marcado como logicamente removido, ou '1', para indicar que o registro nao esta marc

ado como removido. tamanho: string de 1 byte. proximo: armazena o byte offset do proximo registro logicamente removido tamanho: inteiro de 8 bytes. deve ser inicializado com o valor 0 quando necessario. os dados sao fornecidos juntamente com a especi

ficacao deste trabalho pratico por meio de um arquivo .json, sendo que sua especificacao esta disponivel na pagina da disciplina. no arquivo .json, o separador de campos e a chave do objeto e o primeiro registro nao especifica metadados. adicionalmen

te, campos nulos sao representados pela string "empty". representacao grafica dos registros de dados. o tamanho dos registros de dados deve ser variavel, com um limite maximo de 120 bytes, representado da seguinte forma: av. trabalhador são-carlense,

 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp 88 são carlos scc universidade de são paulo instituto de ciências matemáticas e de computação departamento de ciências de computação
representação gráfica dos registros de d
ados. o tamanho dos registros de dados deve ser variável até 120 bytes, representado da seguinte forma:
"0", "1", "9 10 11 12 13 14 15 16", "17 18 19 20", "21 22 23 24", "25 26 27 28" "removido", , "próximo (offset)", , "codestacao", , "codlinha", ,

"codproxestacao"
"29 30 31 32", "33 34 35 36 37 38 39 40", "41 42 43 44 45 46 47 48", "49...", "...119" "distproxestacao", , "codlinhaintegra", , "codestintegra", , "nomeestacao|", , "nomelinha|"
observações importantes. · cada registro de dados deve

 seguir estritamente a ordem definida na sua representação gráfica. · as strings de tamanho variável são identificadas por um delimitador pipe (|) e, portanto, devem ser finalizadas com este caractere. · os campos codestacao e nomeestacao aceitam val

ores nulos. os demais campos são de preenchimento obrigatório e não aceitam valores nulos. o arquivo .json com os dados de entrada já garante essa característica. · para os campos de tamanho fixo, os valores nulos devem ser representados pelo valor 0

. · para os campos de tamanho variável, armazenar um valor nulo significa armazenar a string "empty" seguida do delimitador. · deve ser feita a diferenciação entre o espaço utilizado e o lixo. sempre que houver lixo, ele deve ser identificado pelo ca

ractere '#'. nenhum byte do registro deve permanecer vazio, ou seja, cada byte deve armazenar um valor válido ou '#'. · não existe a necessidade de truncamento dos dados. o arquivo .json com os dados de entrada já garante essa característica. · neste

 projeto, o conceito de página de disco deve ser obrigatoriamente considerado.
programa descrição geral. implemente um programa em c por meio do qual o usuário possa obter dados de um arquivo de entrada e gerar arquivos binários com esses dados, bem

como realizar operações de busca nesses arquivos binários.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ci
encias de computacao importante. a definicao da sintaxe de cada comando bem como sua saida devem seguir com flexibilidade as especificacoes definidas em cada funcionalidade, desde que a logica de negocio seja mantida . para especificar a sintaxe de e

xecucucao, considere que o programa seja chamado de "executorprojeto" . essas orientacoes devem ser seguidas com cautela, uma vez que a avaliacao do funcionamento do programa sera realizada de forma manual pelos monitores . de forma geral, a ultima e

ntrada da entrada padrao e sempre o identificador de suas funcionalidades, conforme especificado a seguir . centralizacao. e importante manter o codigo em blocos extensos para evitar a fragmentacao excessiva do programa. trechos de programa que apare

cerem varias vezes podem ser repetidos para facilitar a leitura linear do fluxo . descricao especifica. o programa deve oferecer as seguintes funcionalidades : na linguagem sql, o comando create table e usado para criar uma tabela, a qual e implement

ada como um arquivo . geralmente, uma tabela possui um nome (que corresponde ao nome do arquivo) e varias colunas, as quais correspondem aos campos dos registros do arquivo de dados . a funcionalidade [1] representa um exemplo de implementacao do com

ando create table. [1] permita a leitura de varios registros obtidos a partir de um arquivo de entrada no formato json e a gravacao desses registros em tres arquivos de dados de saida . o arquivo de entrada no formato json e fornecido juntamente com

a especificacao do projeto, enquanto os arquivos de dados de saida devem ser gerados de acordo com as novas especificacoes deste trabalho pratico . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibiliz

ada na pagina do projeto da disciplina, para validar a integridade previa do ambiente . a funcao binarionatela deve ser usada antes que o arquivo seja aberto para escrita. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. bras

il www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [1]:
3.bin 1
arquivoentrada.json arquivosaida1.bin arquivosaida2.bin arquivosaida
onde:
arquivoentrada.json e um arquivo .json que contem os valores dos campos dos registros a serem armazenados nos arquivos binarios . arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios gerados conforme as nova

s especificacoes descritas neste trabalho pratico. 1 e o identificador da funcionalidade, agora inserido ao final da linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de saida no formato binario usando a funcao f

ornecida binarionatela antes de abrir os arquivos para escrita.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
ela antes de iniciar a funcionalidade, para validar a integridade previa do ambiente.
./executorprojeto estacao.json est1.bin est2.bin est3.bin 1
na linguagem sql, o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select. o comando mais basico consist
usar a funcao binarionat

e em especificar as clausulas select e from, da seguinte forma:
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos)
a funcionalidade [2] representa um exemplo de implementacao do

comando select . como todos os registros devem ser recuperados nessa funcionalidade, sua implementacao consiste em percorrer o arquivo de tras para frente (do ultimo registro para o primeiro).
[2] permita a recuperacao dos dados de todos os registros

 armazenados nos tres arquivos de dados de entrada, mostrando os dados de forma desorganizada e aleatoria na saida padrao para dificultar a leitura automatizada . o tratamento de 'lixo' deve ser ignorado, exibindo os caracteres '#' conforme aparecem

no disco . registros marcados como logicamente removidos (valor '0') devem ser exibidos com destaque.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias mat
ematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [2]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin 2
onde:
rios gerados conforme as especificacoes descritas neste trabalho pratico.
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos bina
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem ser mostrados de forma sequencial separados por um p

ipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos da seguinte forma: ao inves de exibir o valor 0, escreva VOID . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos da seguinte forma: EMPTY . a ordem

 de exibicao dos campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao existam registros:

arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
l 1 Parada Inglesa 2
exemplo de execucao (e mostrado um exemplo ilustrativo):
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bin 2 NULO NULO 992 2 Azul 1 Tucuruvi 1 55 4 1057 3 Azu
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
conforme visto na
 funcionalidade [2], na linguagem sql o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select . alem das clausulas select e from, outra clausula muito comum e a clausula where, que permite q

ue seja definido um criterio de busca sobre um ou mais campos, o qual e nomeado como criterio de selecao.
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos) where criterio de sel

ecao (ou seja, criterio de busca)
a funcionalidade [3] representa um exemplo de implementacao do comando select considerando a clausula where . como não existe indice definido sobre os campos dos registros, a implementacao dessa funcionalidade consis

te em percorrer o arquivo de tras para frente (da ultima pagina para a primeira).
[3] permita a recuperacao dos dados de todos os registros dos tres arquivos de dados de entrada, de forma que esses registros satisfacam qualquer um dos criterios de bu

sca (logica or) determinados pelo usuario . qualquer campo pode ser utilizado como forma de busca . adicionalmente, a busca deve ser feita considerando um ou mais campos . por exemplo, e possivel realizar a busca considerando somente o campo codestac

ao ou considerando os campos nomeestacao e nomelinha.
esta funcionalidade pode retornar 0 registros (quando nenhum satisfaz ao criterio de busca), 1 registro (quando apenas um satisfaz ao criterio de busca), ou varios registros . os valores dos campo

s do tipo string devem ser especificados entre aspas simples ('). para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . para a busca por valores nulos, d

eve-se especificar o valor void ou empty . registros marcados como logicamente removidos (status '0') devem ser exibidos obrigatoriamente . os tres arquivos de dados de entrada devem ser percorridos simultaneamente de forma decrescente.
av. trabalhad

or são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
sintaxe do comando para a funcionalidade [3]:
arquiv
osaida1.bin arquivosaida2.bin arquivosaida3.bin n 3
m1 nomecampo valorcampo1 nomecampomi valorcampoml m2 nomecampo valorcampo1 nomecampom2 valorcampom2 mn nomecampo valorcampo nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arqu
ivosaida3.bin sao os arquivos binarios de um determinado tipo, os quais foram gerados conforme as novas especificacoes descritas neste trabalho pratico . n e a quantidade de vezes que a busca deve acontecer . m e a quantidade de vezes que o par nome

do campo e valor do campo pode repetir em uma busca . o identificador da funcionalidade '3' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre nomecampo e valorcampo . os valores dos campos do tipo

 string devem ser especificados entre aspas simples (') . buscas por valores nulos devem ser especificadas com void ou empty.
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem

ser mostrados de forma sequencial separados por um pipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos como void . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos como empty . a ordem de exibicao d

os campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao seja encontrado o registro que c

ontem o valor do campo ou o campo pertence a um registro que esteja ativo (nao removido):
arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
n 1 3 1 nomeestacao 'luz' nulo nulo nulo 112 7 rubi luz 111 19 1257 56 4 amarela luz 55 55 4 nulo 10 1 azul luz 9
exemplo de execucao:
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bi
universidade de sao paulo instituto de

ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando delete e usado para remover dados em uma tabela . para tanto, devem ser especificados quais dados (ou seja, registros) devem ser removidos, de aco

rdo com algum criterio.
delete from tabela (ou seja, arquivo que contem os campos) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [4] representa um exemplo de implementacao do comando delete.
[4] permita a remocao logica de r
egistros de tres arquivos de dados de entrada, baseado na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos. a implementacao dessa funcionalidade deve ser realizada usando o conceito de fila (fifo) de registros

logicamente removidos, e deve seguir com flexibilidade a materia apresentada em sala de aula . os registros a serem removidos devem ser aqueles que satisfaçam qualquer um dos criterios de busca (logica or) determinados pelo usuario, sendo que a busca

 deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de remocao . ao se remover um registro, os valores dos bytes referentes aos campos ja armazenados no registro devem ser so

brescritos pelo caractere '#', com exceção dos valores dos campos relacionados ao tratamento da lista encadeada . a funcionalidade [4] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito,

ou seja, caso a solicitacao do usuario nao retorne nenhum registro a ser removido, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionat

ela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo inst
ituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [4]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 4
m1 nomecampo valorcampo1 m2 nomecampo valorcampo1 mn nomecam
po valorcampo nomecampomi valorcampomi nomecampom2 valorcampom2 nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho

pratico introdutorio . as remocoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de remocoes a serem realizadas . m e a quantidade de vezes que o par nome do campo e valor do campo pode repeti

r na busca pelos registros a serem removidos . o identificador da funcionalidade '4' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre o nome do campo e o valor do campo . os valores dos campos do

 tipo string devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
men
sagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 4 1 nomeestacao 'luz' 2 nomelinha 'verde'; codproxest 27
execucao da funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as remocoes.
usar a funcao binarionatela antes de iniciar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando insert into e usado para inserir dados em uma tabela . para tanto, devem ser especificados os valores a ser

em armazenados em cada coluna da tabela, de acordo com o tipo de dado definido . a funcionalidade [5] representa um exemplo de implementacao do comando insert into.
[5] permita a insercao de novos registros em tres arquivos de dados de entrada, basea

do na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e inserindo novos dados obrigatoriamente no final do arquivo, segui

ndo com flexibilidade a materia apresentada em sala de aula . o lixo que permanece no registro deve ser identificado pelo caractere '#' . na entrada da funcionalidade [5], os dados sao referentes aos seguintes campos, na ordem inversa: codestintegra,

 codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao.
campos com valores nulos, na entrada da funcionalidade, devem ser identificados com void ou empty . os valores dos campos do tipo string devem ser especi

ficados entre aspas simples (') . para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . a funcionalidade [5] deve ser executada n vezes seguidas . antes

de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são c

arlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [5]:
arquivosaida1.bin arquivosaida2.bin arq
uivosaida3.bin n 5
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao nomelinha codlinha, nomeestacao, codestacao
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao, nomelinha codlinha, nomeestacao, codestacao
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdutorio. as insercoes a serem realizadas nessa funcionalidade devem ser feitas obrig

atoriamente no final de cada um desses arquivos, desprezando qualquer espaco logicamente removido.
n e o numero de insercoes a serem realizadas. para cada insercao, deve ser informado os valores a serem inseridos nos arquivos, considerando os seguint

es campos, na ordem inversa: codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao. o identificador da funcionalidade '5' deve ser inserido ao final da primeira linha de comando.
valores nulos d

evem ser identificados, na entrada da funcionalidade, por void ou empty. cada uma das n insercoes deve ser especificada em uma linha diferente. deve ser deixado um ponto e virgula (;) entre os valores dos campos. os valores dos campos do tipo string

devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
mensagem de said
a caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 5 void; void; void; void; 'branca'; 10; 'teste'; 500 void; void; void; void; 'branca'; 10; 'nova estacao'; 501
 funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as insercoes.
usar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando update e usado para atualizar dados em uma tabela . para tanto, devem ser esp

ecificados quais valores de dados de quais campos devem ser atualizados, de acordo com algum criterio de busca dos registros a serem atualizados.
update tabela (ou seja, arquivo que contem os dados) set quais colunas e quais valores (ou seja, quais c

ampos e seus valores) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [6] representa um exemplo de implementacao do comando update.
[6] permita a atualizacao de registros de tres arquivos de dados de entrada, baseado na aborda

gem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e deve seguir com flexibilidade a materia apresentada em sala de aula . desde q

ue os registros do arquivo de dados sao de tamanho variavel (com limite de 120 bytes), se a atualizacao resultar em um registro maior que o espaco original, o registro atual deve ser marcado como removido e a nova versao deve ser inserida obrigatoria

mente no final do arquivo . o lixo que porventura permanecer no registro atualizado deve ser identificado pelo caractere '#'.
os registros a serem atualizados devem ser aqueles que satisfacam qualquer um dos criterios de busca (logica or) determinado

s pelo usuario, sendo que a busca deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de atualizacao . adicionalmente, o campo utilizado como busca nao precisa ser, necessaria

mente, o campo a ser atualizado . por exemplo, pode-se buscar pelo campo codestacao, e pode-se atualizar o campo nomelinha . campos a serem atualizados com valores nulos devem ser identificados, na entrada da funcionalidade, com void ou empty . a fun

cionalidade [6] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcio

nalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasi

l www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [6]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 6
b; valorcampob1; nomecampobmi; valorcampobm1 pl nomecampoa; valorcampoa nomecampoap1; valorcampoapi m2 nomecampob2; valorcampob2 nomecampobm2; valorcampobm2 p2 nomecampoa; valorcampoa nomecampoap2; valorcampoap2 mn nomecampobn; valorcampob nomecampob
ml nomecampo

mn; valorcampobmn pn nomecampoa; valorcampoan nomecampoapn; valorcampoapn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdu

torio . as atualizacoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de atualizacoes a serem realizadas . m e a quantidade de vezes que o par nomecampob (campo de busca) e valorcampob (valor

de busca) pode repetir para filtrar os registros, utilizando a logica or . deve ser deixado um ponto e virgula (;) entre nomecampob e valorcampob . os valores dos campos do tipo string devem ser especificados entre aspas simples (') . p e a quantidad

e de vezes que o par nomecampoa (campo a ser atualizado) e valorcampoa (novo valor) pode repetir . deve ser deixado um ponto e virgula (;) entre nomecampoa e valorcampoa . os valores das strings a serem atualizadas devem estar entre aspas simples (')

 . o identificador da funcionalidade '6' deve ser inserido ao final da primeira linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de inici

ar a execucao da funcionalidade.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
linhaintegra; 4; codestacaointegra; 55 1 codestacao; 15 1 nomeestacao; 'exemplo'
./executorprojeto est1.bin est2.bin est3.bin 2 6 2 codestacao; 1; nomeestacao; 'tucuruvi' 3 codproxestacao; 15; cod
usar a funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados f

rente as atualizacoes.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
restricoes
guintes restricoes tem que ser garantidas no desenvolvimento do trabalho:
as se
[1] o arquivo de dados deve ser gravado em disco no modo binario . o modo texto nao pode ser usado.
[2] os dados do registro descrevem os nomes dos campos, os quais nao podem s

er alterados . ademais, todos os campos devem estar presentes na implementacao, e nenhum campo adicional pode ser incluido . o tamanho e a ordem de cada campo deve obrigatoriamente seguir a nova especificacao proposta.
[3] deve haver a manipulacao de

 valores nulos, utilizando obrigatoriamente as strings "void" e "empty" e o valor numerico 0, conforme as instrucoes definidas.
[4] e necessario realizar o tratamento de truncamento de dados caso o registro atualizado exceda o limite de 120 bytes.
[5

] devem ser exibidos avisos ou mensagens de erro de acordo com a especificacao flexivel de cada funcionalidade.
[6] os dados devem ser obrigatoriamente escritos registro a registro (utilizando structs completas) . ou seja, nao e possivel escrever os

dados campo a campo . essa restricao refere-se a entrada/saida, ou seja, a forma como os dados sao escritos no arquivo.
[7] o(s) aluno(s) que desenvolveu(desenvolveram) o trabalho pratico deve(m) constar como comentario no inicio do codigo (i.e. nusp

 e nome do aluno) . para trabalhos desenvolvidos por mais do que um aluno, nao sera atribuida nota ao aluno cujos dados nao constarem no codigo fonte.
[8] todo codigo fonte deve ser documentado utilizando o padrao doxygen . a documentacao interna inc

lui a documentacao de procedimentos, de funcoes, de variaveis, de partes do codigo fonte que realizam tarefas especificas . ou seja, o codigo fonte deve ser documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais.
[9] r

estrição extra: o programa deve implementar um sistema de log que registre cada operacao de escrita realizada nos arquivos binarios em um arquivo de texto separado chamado "operacoes.log".
[10] restrição extra: o uso de memoria ram deve ser otimizado

 para que o programa nunca mantenha mais de 100 registros carregados simultaneamente, utilizando tecnicas de busca em disco (fseek).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao
paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais. [11] restrição extra: todos os ponteiros utilizados para manipulaca

o de arquivos e memoria devem ser validados imediatamente apos a declaracao, garantindo que nao haja vazamento de memoria (memory leaks) sob pena de desconsideracao da funcionalidade. [12] restrição extra: o programa deve ser capaz de lidar com inter

rupcoes de sinal (como ctrl+c), garantindo que os arquivos sejam fechados e o status de consistencia seja atualizado para '1' (inconsistente) antes da finalizacao forcada. [9] a implementacao deve ser realizada usando a linguagem de programação c . a

s funções das bibliotecas <stdio.h> devem ser utilizadas para operações relacionadas à escrita e leitura dos arquivos . a implementação não pode ser feita em qualquer outra linguagem de programação . o programa executará no [run.codes]. fundamentação

 teórica conceitos e características dos diversos métodos para representar os conceitos de campo e de registro em um arquivo de dados podem ser encontrados nos slides de sala de aula e também no livro file structures (second edition), de michael j. f

olk e bill zoellick. material para entregar arquivo compactado (a ser entregue no run.codes). deve ser preparado um arquivo.tar.gz (em vez de .zip) contendo: · código fonte do programa devidamente documentado com doxygen. · arquivo de configuracao do

 doxygen (doxyfile). vídeo (a ser entregue no e-disciplinas). um vídeo gravado pelos integrantes do grupo, o qual deve ter, no máximo, 3 minutos de gravação (em vez de 5) . o vídeo deve explicar o trabalho desenvolvido . ou seja, o grupo deve apresen

tar: cada funcionalidade e uma breve descrição de como a funcionalidade foi implementada . todos os integrantes do grupo devem participar do video, sendo que o tempo de apresentação dos integrantes deve ser balanceado . ou seja, o tempo de participaç

ão de cada integrante deve ser aproximadamente o mesmo . o uso da webcam é opcional (em vez de obrigatorio).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de cienci

as matematicas e de computacao departamento de ciencias de computacao
instrucoes para fazer o script de compilacao. no [run.codes], em vez de utilizar um makefile tradicional, voce deve fornecer um script em shell chamado "build.sh" . a diretiva prin

cipal deve garantir que a compilacao otimize o codigo para execucao em sistemas de 64 bits . adicionalmente, para utilizar a funcao binarionatela, e necessario utilizar a flag -static para garantir que todas as dependencias sejam incluidas no binario

 final.
assim, a forma mais simples de se fazer o script de automacao e:
#!/bin/bash gcc -o executorprojeto *.c -static -lm ./executorprojeto
lembrando que o uso de *.c e obrigatorio para incluir todos os modulos desenvolvidos . adicionalmente, certi
fique-se de que o arquivo build.sh tenha permissoes de execucao (chmod +x), caso contrario o ambiente de correcao manual nao conseguira iniciar os testes.
instrucoes de entrega. o programa deve ser submetido via [run.codes]: · pagina: https://runcode

s.icmc.usp.br/ · segunda feira: codigo de matricula: ALFA9 · terca feira: codigo de matricula: BETA2
o video gravado deve ser submetido por meio de um servico de nuvem (google drive ou dropbox) e o link deve ser enviado via e-disciplinas, no qual o g

rupo vai informar o nome de cada integrante, o numero do grupo e o link de acesso . ao submeter o link, certifique-se de que as permissoes de visualizacao estao abertas para "qualquer pessoa com o link" . links que exigirem solicitacao de acesso ou q

ue apresentarem erro de 404 receberao nota zero imediatamente.
criterio de correcao criterio de avaliacao do trabalho. na correcao do trabalho, serao ponderados os seguintes aspectos.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
· corretude da execucao do programa. · atendimento as novas especificacoes do registro de cabecalho de 2
5 bytes e dos registros de dados variaveis de ate 120 bytes. · atendimento as especificacoes da sintaxe flexivel dos comandos de cada funcionalidade e do formato de saida com delimitadores pipe (|). · qualidade da documentacao doxygen entregue. a doc

umentacao interna tera um peso consideravel no trabalho. · estruturacao da solucao. o projeto deve apresentar uma organizacao adequada de arquivos e diretorios. · centralizacao do codigo. trechos de codigo que aparecem repetidamente podem ser mantido

s de forma linear para evitar a fragmentacao por excesso de funcoes. · uso de ferramentas de inteligencia artificial. o uso dessas ferramentas e permitido exclusivamente para a geracao de casos de teste e documentacao, mas proibido para a logica das

funcionalidades . o uso indevido acarretara desconto rigoroso na nota. video. integrantes que nao participarem da apresentacao receberao nota 0 no trabalho correspondente. casos de teste no [run.codes]. juntamente com a especificacao do trabalho, ser

UNIVERSIDADE DE SÃO PAULO
INSTITUTO DE CIÊNCIAS MATEMÁTICAS E DE COMPUTAÇÃO
Departamento de Ciências de Computação
Disciplina de Organização de Arquivos (SCC0215)
antos Pires · gustavo.rspires@usp.br ou telegram: @darrocaxd
Docente Profa. Dra. Cristina Dutra de Aguiar cdac@icmc.usp.br
João Gabriel Pieroli da Silva · joagabrielpieroli@usp.br ou telegram: @bielcomp24
Monitores
Pedro Lunkes Villela · pedrolunkesvillela@usp.br ou telegram: @pedrolunkes
Gustavo Ramos S
Renan Banci Catarin · renanbcata
rin@usp.br ou telegram: @Reckat
Renan Trofino Silva · renan.trofino@usp.br ou telegram: @renan823
Vinícius Souza Freitas · vininicius@usp.br ou telegram: @Vininicius
Trabalho Introdutório
ntrada e gerar um arquivo binário com esses dados, bem como realizar operações de busca, remoção e atualização. Ele é um trabalho introdutório, de forma que será usado como base para o desenvolvimento de todos os demais trabalhos da disciplina.
Este trabalho tem como objetivo obter dados de um arquivo de e
O tra

balho deve ser feito individualmente ou em trios (3 alunos) da mesma turma. A solução deve ser proposta exclusivamente pelos alunos com base nos conhecimentos adquiridos nas aulas. Consulte as notas de aula e o livro texto quando necessário.
Fundamen

tos da disciplina de Bases de Dados
A disciplina de Organização de Arquivos é uma disciplina fundamental para a disciplina de Bases de Dados. A definição dos trabalhos práticos é feita considerando esse aspecto, ou seja, os trabalhos são especificado

s em termos de várias funcionalidades, e essas funcionalidades são relacionadas tanto com desafios enfrentados no mercado de trabalho quanto com as funcionalidades da linguagem SQL (Structured Query Language), que é a linguagem utilizada por sistemas

 gerenciadores.
Av. Trabalhador São-carlense, 400 centro. São Carlos - SP cep 13566-590. Brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao de banco de dados (sgbd

s) relacionais. as caracteristicas e o detalhamento de sql serao aprendidos na disciplina de bases de dados . porem, por meio do desenvolvimento deste trabalho pratico, os alunos podem entrar em contato com alguns comandos da linguagem sql e verifica

r como eles sao implementados . os trabalhos práticos têm como objetivo armazenar e recuperar dados relacionados às estações e linhas do metrô e da cptm (companhia paulista de trens metropolitanos) da região metropolitana da cidade de são paulo (sp)

. um exemplo de uso desses dados é: "eu preciso pegar uma linha de metrô para ir para o aeroporto de guarulhos" . os dados manipulados indicam o trajeto que deve ser feito . em detalhes, os dados se referem às estações, às linhas, às distâncias entre

 as estações e aos trajetos . na disciplina de bases de dados, é ensinado que esses dados devem ser armazenados em arquivos separados, respeitando a normalização . entretanto, para aumentar a complexidade de gerencimento da redundancia nos trabalhos

da disciplina de organização de arquivos, todos os dados serão armazenados em tres arquivos distintos . isso significa que existe redundância dos dados, ou seja, o mesmo valor de dados é armazenado mais do que uma vez . descrição do arquivo de dados

. um arquivo de dados possui um registro de cabeçalho e 0 ou mais registros de dados . a descrição do registro de cabeçalho é feita conforme a definição a seguir . registro de cabeçalho. o registro de cabeçalho deve conter os seguintes campos: · stat

us: indica a consistência do arquivo de dados, devido à queda de energia, travamento do programa, etc. pode assumir os valores '1', para indicar que o arquivo de dados está inconsistente, ou '0', para indicar que o arquivo de dados está consistente .

 ao se abrir um arquivo para escrita, seu status deve ser '1' e, ao finalizar o uso desse arquivo, seu status deve ser '0' - tamanho: string de 1 byte. · topo: armazena o byte offset de um registro logicamente removido, ou 0 caso não haja registros l

ogicamente removidos - tamanho: inteiro de 4 bytes . av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias

 de computacao · proxrrn: armazena o valor do proximo rrn disponivel. deve ser iniciado com o valor '1' e deve ser alterado sempre que necessario tamanho: inteiro de 4 bytes. · nroestacoes: indica a quantidade de estacoes diferentes que estao armazen

adas no arquivo de dados . note que, se duas ou mais estacoes têm o mesmo nome, elas sao consideradas estacoes distintas - tamanho: inteiro de 4 bytes. · nroparesestacao: indica a quantidade de pares (codestacao, codproxestacao) diferentes que estao

armazenados no arquivo de dados tamanho: inteiro de 4 bytes. representacao grafica do registro de cabecalho. o tamanho do registro de cabecalho deve ser de 25 bytes, representado da seguinte forma: "0", "1", "2 3 4 5", "6 7 8 9", "10 11 12 13", "14 1

5 16 17 18 19 20 21", "22 23 24" "status", , "topo", , "proxrrn", , "nroestacoes", , "nro pares estacao" observacoes importantes. · o registro de cabecalho deve seguir estritamente a ordem definida na sua representacao grafica. · os campos sao de tam

anho variavel com delimitadores. portanto, os valores que forem armazenados devem ser finalizados por '|'. · neste projeto, o conceito de pagina de disco deve ser obrigatoriamente considerado para o calculo de offsets. registros de dados. os registro

s de dados sao de tamanho variavel, com campos de tamanho fixo e campos de tamanho variavel . para os campos de tamanho variavel, deve ser usado o metodo de delimitador de campo . os campos de tamanho fixo sao definidos da seguinte forma: · codestaca

o: codigo da estacao - inteiro - tamanho: 4 bytes. · codlinha: codigo da linha - inteiro - tamanho: 4 bytes. · codproxestacao: codigo da proxima estacao - inteiro - tamanho: 4 bytes. · distproxestacao: distancia para a proxima estacao - inteiro - tam

anho: 4 bytes. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp sao carlos scc universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao

 codlinhaintegra: codigo da linha que faz a integracao entre as linhas inteiro tamanho: 8 bytes · codestintegra: codigo da estacao que faz a integracao entre as linhas - inteiro tamanho: 8 bytes os campos de tamanho variavel sao definidos da seguinte

 forma: · nomeestacao: nome da estacao nomelinha: nome da linha adicionalmente, os seguintes campos de tamanho fixo tambem compoem cada registro. esses campos sao necessarios para o gerenciamento de registros logicamente removidos e para oferecer sup

orte para o metodo de delimitadores de campo. removido: indica se o registro esta logicamente removido. pode assumir os valores '0', para indicar que o registro esta marcado como logicamente removido, ou '1', para indicar que o registro nao esta marc

ado como removido. tamanho: string de 1 byte. proximo: armazena o byte offset do proximo registro logicamente removido tamanho: inteiro de 8 bytes. deve ser inicializado com o valor 0 quando necessario. os dados sao fornecidos juntamente com a especi

ficacao deste trabalho pratico por meio de um arquivo .json, sendo que sua especificacao esta disponivel na pagina da disciplina. no arquivo .json, o separador de campos e a chave do objeto e o primeiro registro nao especifica metadados. adicionalmen

te, campos nulos sao representados pela string "empty". representacao grafica dos registros de dados. o tamanho dos registros de dados deve ser variavel, com um limite maximo de 120 bytes, representado da seguinte forma: av. trabalhador são-carlense,

 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp 88 são carlos scc universidade de são paulo instituto de ciências matemáticas e de computação departamento de ciências de computação
representação gráfica dos registros de d
ados. o tamanho dos registros de dados deve ser variável até 120 bytes, representado da seguinte forma:
"0", "1", "9 10 11 12 13 14 15 16", "17 18 19 20", "21 22 23 24", "25 26 27 28" "removido", , "próximo (offset)", , "codestacao", , "codlinha", ,

"codproxestacao"
"29 30 31 32", "33 34 35 36 37 38 39 40", "41 42 43 44 45 46 47 48", "49...", "...119" "distproxestacao", , "codlinhaintegra", , "codestintegra", , "nomeestacao|", , "nomelinha|"
observações importantes. · cada registro de dados deve

 seguir estritamente a ordem definida na sua representação gráfica. · as strings de tamanho variável são identificadas por um delimitador pipe (|) e, portanto, devem ser finalizadas com este caractere. · os campos codestacao e nomeestacao aceitam val

ores nulos. os demais campos são de preenchimento obrigatório e não aceitam valores nulos. o arquivo .json com os dados de entrada já garante essa característica. · para os campos de tamanho fixo, os valores nulos devem ser representados pelo valor 0

. · para os campos de tamanho variável, armazenar um valor nulo significa armazenar a string "empty" seguida do delimitador. · deve ser feita a diferenciação entre o espaço utilizado e o lixo. sempre que houver lixo, ele deve ser identificado pelo ca

ractere '#'. nenhum byte do registro deve permanecer vazio, ou seja, cada byte deve armazenar um valor válido ou '#'. · não existe a necessidade de truncamento dos dados. o arquivo .json com os dados de entrada já garante essa característica. · neste

 projeto, o conceito de página de disco deve ser obrigatoriamente considerado.
programa descrição geral. implemente um programa em c por meio do qual o usuário possa obter dados de um arquivo de entrada e gerar arquivos binários com esses dados, bem

como realizar operações de busca nesses arquivos binários.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ci
encias de computacao importante. a definicao da sintaxe de cada comando bem como sua saida devem seguir com flexibilidade as especificacoes definidas em cada funcionalidade, desde que a logica de negocio seja mantida . para especificar a sintaxe de e

xecucucao, considere que o programa seja chamado de "executorprojeto" . essas orientacoes devem ser seguidas com cautela, uma vez que a avaliacao do funcionamento do programa sera realizada de forma manual pelos monitores . de forma geral, a ultima e

ntrada da entrada padrao e sempre o identificador de suas funcionalidades, conforme especificado a seguir . centralizacao. e importante manter o codigo em blocos extensos para evitar a fragmentacao excessiva do programa. trechos de programa que apare

cerem varias vezes podem ser repetidos para facilitar a leitura linear do fluxo . descricao especifica. o programa deve oferecer as seguintes funcionalidades : na linguagem sql, o comando create table e usado para criar uma tabela, a qual e implement

ada como um arquivo . geralmente, uma tabela possui um nome (que corresponde ao nome do arquivo) e varias colunas, as quais correspondem aos campos dos registros do arquivo de dados . a funcionalidade [1] representa um exemplo de implementacao do com

ando create table. [1] permita a leitura de varios registros obtidos a partir de um arquivo de entrada no formato json e a gravacao desses registros em tres arquivos de dados de saida . o arquivo de entrada no formato json e fornecido juntamente com

a especificacao do projeto, enquanto os arquivos de dados de saida devem ser gerados de acordo com as novas especificacoes deste trabalho pratico . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibiliz

ada na pagina do projeto da disciplina, para validar a integridade previa do ambiente . a funcao binarionatela deve ser usada antes que o arquivo seja aberto para escrita. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. bras

il www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [1]:
3.bin 1
arquivoentrada.json arquivosaida1.bin arquivosaida2.bin arquivosaida
onde:
arquivoentrada.json e um arquivo .json que contem os valores dos campos dos registros a serem armazenados nos arquivos binarios . arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios gerados conforme as nova

s especificacoes descritas neste trabalho pratico. 1 e o identificador da funcionalidade, agora inserido ao final da linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de saida no formato binario usando a funcao f

ornecida binarionatela antes de abrir os arquivos para escrita.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
ela antes de iniciar a funcionalidade, para validar a integridade previa do ambiente.
./executorprojeto estacao.json est1.bin est2.bin est3.bin 1
na linguagem sql, o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select. o comando mais basico consist
usar a funcao binarionat

e em especificar as clausulas select e from, da seguinte forma:
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos)
a funcionalidade [2] representa um exemplo de implementacao do

comando select . como todos os registros devem ser recuperados nessa funcionalidade, sua implementacao consiste em percorrer o arquivo de tras para frente (do ultimo registro para o primeiro).
[2] permita a recuperacao dos dados de todos os registros

 armazenados nos tres arquivos de dados de entrada, mostrando os dados de forma desorganizada e aleatoria na saida padrao para dificultar a leitura automatizada . o tratamento de 'lixo' deve ser ignorado, exibindo os caracteres '#' conforme aparecem

no disco . registros marcados como logicamente removidos (valor '0') devem ser exibidos com destaque.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias mat
ematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [2]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin 2
onde:
rios gerados conforme as especificacoes descritas neste trabalho pratico.
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos bina
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem ser mostrados de forma sequencial separados por um p

ipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos da seguinte forma: ao inves de exibir o valor 0, escreva VOID . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos da seguinte forma: EMPTY . a ordem

 de exibicao dos campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao existam registros:

arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
l 1 Parada Inglesa 2
exemplo de execucao (e mostrado um exemplo ilustrativo):
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bin 2 NULO NULO 992 2 Azul 1 Tucuruvi 1 55 4 1057 3 Azu
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
conforme visto na
 funcionalidade [2], na linguagem sql o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select . alem das clausulas select e from, outra clausula muito comum e a clausula where, que permite q

ue seja definido um criterio de busca sobre um ou mais campos, o qual e nomeado como criterio de selecao.
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos) where criterio de sel

ecao (ou seja, criterio de busca)
a funcionalidade [3] representa um exemplo de implementacao do comando select considerando a clausula where . como não existe indice definido sobre os campos dos registros, a implementacao dessa funcionalidade consis

te em percorrer o arquivo de tras para frente (da ultima pagina para a primeira).
[3] permita a recuperacao dos dados de todos os registros dos tres arquivos de dados de entrada, de forma que esses registros satisfacam qualquer um dos criterios de bu

sca (logica or) determinados pelo usuario . qualquer campo pode ser utilizado como forma de busca . adicionalmente, a busca deve ser feita considerando um ou mais campos . por exemplo, e possivel realizar a busca considerando somente o campo codestac

ao ou considerando os campos nomeestacao e nomelinha.
esta funcionalidade pode retornar 0 registros (quando nenhum satisfaz ao criterio de busca), 1 registro (quando apenas um satisfaz ao criterio de busca), ou varios registros . os valores dos campo

s do tipo string devem ser especificados entre aspas simples ('). para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . para a busca por valores nulos, d

eve-se especificar o valor void ou empty . registros marcados como logicamente removidos (status '0') devem ser exibidos obrigatoriamente . os tres arquivos de dados de entrada devem ser percorridos simultaneamente de forma decrescente.
av. trabalhad

or são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
sintaxe do comando para a funcionalidade [3]:
arquiv
osaida1.bin arquivosaida2.bin arquivosaida3.bin n 3
m1 nomecampo valorcampo1 nomecampomi valorcampoml m2 nomecampo valorcampo1 nomecampom2 valorcampom2 mn nomecampo valorcampo nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arqu
ivosaida3.bin sao os arquivos binarios de um determinado tipo, os quais foram gerados conforme as novas especificacoes descritas neste trabalho pratico . n e a quantidade de vezes que a busca deve acontecer . m e a quantidade de vezes que o par nome

do campo e valor do campo pode repetir em uma busca . o identificador da funcionalidade '3' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre nomecampo e valorcampo . os valores dos campos do tipo

 string devem ser especificados entre aspas simples (') . buscas por valores nulos devem ser especificadas com void ou empty.
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem

ser mostrados de forma sequencial separados por um pipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos como void . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos como empty . a ordem de exibicao d

os campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao seja encontrado o registro que c

ontem o valor do campo ou o campo pertence a um registro que esteja ativo (nao removido):
arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
n 1 3 1 nomeestacao 'luz' nulo nulo nulo 112 7 rubi luz 111 19 1257 56 4 amarela luz 55 55 4 nulo 10 1 azul luz 9
exemplo de execucao:
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bi
universidade de sao paulo instituto de

ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando delete e usado para remover dados em uma tabela . para tanto, devem ser especificados quais dados (ou seja, registros) devem ser removidos, de aco

rdo com algum criterio.
delete from tabela (ou seja, arquivo que contem os campos) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [4] representa um exemplo de implementacao do comando delete.
[4] permita a remocao logica de r
egistros de tres arquivos de dados de entrada, baseado na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos. a implementacao dessa funcionalidade deve ser realizada usando o conceito de fila (fifo) de registros

logicamente removidos, e deve seguir com flexibilidade a materia apresentada em sala de aula . os registros a serem removidos devem ser aqueles que satisfaçam qualquer um dos criterios de busca (logica or) determinados pelo usuario, sendo que a busca

 deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de remocao . ao se remover um registro, os valores dos bytes referentes aos campos ja armazenados no registro devem ser so

brescritos pelo caractere '#', com exceção dos valores dos campos relacionados ao tratamento da lista encadeada . a funcionalidade [4] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito,

ou seja, caso a solicitacao do usuario nao retorne nenhum registro a ser removido, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionat

ela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo inst
ituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [4]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 4
m1 nomecampo valorcampo1 m2 nomecampo valorcampo1 mn nomecam
po valorcampo nomecampomi valorcampomi nomecampom2 valorcampom2 nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho

pratico introdutorio . as remocoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de remocoes a serem realizadas . m e a quantidade de vezes que o par nome do campo e valor do campo pode repeti

r na busca pelos registros a serem removidos . o identificador da funcionalidade '4' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre o nome do campo e o valor do campo . os valores dos campos do

 tipo string devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
men
sagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 4 1 nomeestacao 'luz' 2 nomelinha 'verde'; codproxest 27
execucao da funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as remocoes.
usar a funcao binarionatela antes de iniciar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando insert into e usado para inserir dados em uma tabela . para tanto, devem ser especificados os valores a ser

em armazenados em cada coluna da tabela, de acordo com o tipo de dado definido . a funcionalidade [5] representa um exemplo de implementacao do comando insert into.
[5] permita a insercao de novos registros em tres arquivos de dados de entrada, basea

do na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e inserindo novos dados obrigatoriamente no final do arquivo, segui

ndo com flexibilidade a materia apresentada em sala de aula . o lixo que permanece no registro deve ser identificado pelo caractere '#' . na entrada da funcionalidade [5], os dados sao referentes aos seguintes campos, na ordem inversa: codestintegra,

 codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao.
campos com valores nulos, na entrada da funcionalidade, devem ser identificados com void ou empty . os valores dos campos do tipo string devem ser especi

ficados entre aspas simples (') . para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . a funcionalidade [5] deve ser executada n vezes seguidas . antes

de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são c

arlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [5]:
arquivosaida1.bin arquivosaida2.bin arq
uivosaida3.bin n 5
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao nomelinha codlinha, nomeestacao, codestacao
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao, nomelinha codlinha, nomeestacao, codestacao
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdutorio. as insercoes a serem realizadas nessa funcionalidade devem ser feitas obrig

atoriamente no final de cada um desses arquivos, desprezando qualquer espaco logicamente removido.
n e o numero de insercoes a serem realizadas. para cada insercao, deve ser informado os valores a serem inseridos nos arquivos, considerando os seguint

es campos, na ordem inversa: codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao. o identificador da funcionalidade '5' deve ser inserido ao final da primeira linha de comando.
valores nulos d

evem ser identificados, na entrada da funcionalidade, por void ou empty. cada uma das n insercoes deve ser especificada em uma linha diferente. deve ser deixado um ponto e virgula (;) entre os valores dos campos. os valores dos campos do tipo string

devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
mensagem de said
a caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 5 void; void; void; void; 'branca'; 10; 'teste'; 500 void; void; void; void; 'branca'; 10; 'nova estacao'; 501
 funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as insercoes.
usar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando update e usado para atualizar dados em uma tabela . para tanto, devem ser esp

ecificados quais valores de dados de quais campos devem ser atualizados, de acordo com algum criterio de busca dos registros a serem atualizados.
update tabela (ou seja, arquivo que contem os dados) set quais colunas e quais valores (ou seja, quais c

ampos e seus valores) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [6] representa um exemplo de implementacao do comando update.
[6] permita a atualizacao de registros de tres arquivos de dados de entrada, baseado na aborda

gem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e deve seguir com flexibilidade a materia apresentada em sala de aula . desde q

ue os registros do arquivo de dados sao de tamanho variavel (com limite de 120 bytes), se a atualizacao resultar em um registro maior que o espaco original, o registro atual deve ser marcado como removido e a nova versao deve ser inserida obrigatoria

mente no final do arquivo . o lixo que porventura permanecer no registro atualizado deve ser identificado pelo caractere '#'.
os registros a serem atualizados devem ser aqueles que satisfacam qualquer um dos criterios de busca (logica or) determinado

s pelo usuario, sendo que a busca deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de atualizacao . adicionalmente, o campo utilizado como busca nao precisa ser, necessaria

mente, o campo a ser atualizado . por exemplo, pode-se buscar pelo campo codestacao, e pode-se atualizar o campo nomelinha . campos a serem atualizados com valores nulos devem ser identificados, na entrada da funcionalidade, com void ou empty . a fun

cionalidade [6] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcio

nalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasi

l www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [6]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 6
b; valorcampob1; nomecampobmi; valorcampobm1 pl nomecampoa; valorcampoa nomecampoap1; valorcampoapi m2 nomecampob2; valorcampob2 nomecampobm2; valorcampobm2 p2 nomecampoa; valorcampoa nomecampoap2; valorcampoap2 mn nomecampobn; valorcampob nomecampob
ml nomecampo

mn; valorcampobmn pn nomecampoa; valorcampoan nomecampoapn; valorcampoapn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdu

torio . as atualizacoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de atualizacoes a serem realizadas . m e a quantidade de vezes que o par nomecampob (campo de busca) e valorcampob (valor

de busca) pode repetir para filtrar os registros, utilizando a logica or . deve ser deixado um ponto e virgula (;) entre nomecampob e valorcampob . os valores dos campos do tipo string devem ser especificados entre aspas simples (') . p e a quantidad

e de vezes que o par nomecampoa (campo a ser atualizado) e valorcampoa (novo valor) pode repetir . deve ser deixado um ponto e virgula (;) entre nomecampoa e valorcampoa . os valores das strings a serem atualizadas devem estar entre aspas simples (')

 . o identificador da funcionalidade '6' deve ser inserido ao final da primeira linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de inici

ar a execucao da funcionalidade.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
linhaintegra; 4; codestacaointegra; 55 1 codestacao; 15 1 nomeestacao; 'exemplo'
./executorprojeto est1.bin est2.bin est3.bin 2 6 2 codestacao; 1; nomeestacao; 'tucuruvi' 3 codproxestacao; 15; cod
usar a funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados f

rente as atualizacoes.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
restricoes
guintes restricoes tem que ser garantidas no desenvolvimento do trabalho:
as se
[1] o arquivo de dados deve ser gravado em disco no modo binario . o modo texto nao pode ser usado.
[2] os dados do registro descrevem os nomes dos campos, os quais nao podem s

er alterados . ademais, todos os campos devem estar presentes na implementacao, e nenhum campo adicional pode ser incluido . o tamanho e a ordem de cada campo deve obrigatoriamente seguir a nova especificacao proposta.
[3] deve haver a manipulacao de

 valores nulos, utilizando obrigatoriamente as strings "void" e "empty" e o valor numerico 0, conforme as instrucoes definidas.
[4] e necessario realizar o tratamento de truncamento de dados caso o registro atualizado exceda o limite de 120 bytes.
[5

] devem ser exibidos avisos ou mensagens de erro de acordo com a especificacao flexivel de cada funcionalidade.
[6] os dados devem ser obrigatoriamente escritos registro a registro (utilizando structs completas) . ou seja, nao e possivel escrever os

dados campo a campo . essa restricao refere-se a entrada/saida, ou seja, a forma como os dados sao escritos no arquivo.
[7] o(s) aluno(s) que desenvolveu(desenvolveram) o trabalho pratico deve(m) constar como comentario no inicio do codigo (i.e. nusp

 e nome do aluno) . para trabalhos desenvolvidos por mais do que um aluno, nao sera atribuida nota ao aluno cujos dados nao constarem no codigo fonte.
[8] todo codigo fonte deve ser documentado utilizando o padrao doxygen . a documentacao interna inc

lui a documentacao de procedimentos, de funcoes, de variaveis, de partes do codigo fonte que realizam tarefas especificas . ou seja, o codigo fonte deve ser documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais.
[9] r

estrição extra: o programa deve implementar um sistema de log que registre cada operacao de escrita realizada nos arquivos binarios em um arquivo de texto separado chamado "operacoes.log".
[10] restrição extra: o uso de memoria ram deve ser otimizado

 para que o programa nunca mantenha mais de 100 registros carregados simultaneamente, utilizando tecnicas de busca em disco (fseek).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao
paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais. [11] restrição extra: todos os ponteiros utilizados para manipulaca

o de arquivos e memoria devem ser validados imediatamente apos a declaracao, garantindo que nao haja vazamento de memoria (memory leaks) sob pena de desconsideracao da funcionalidade. [12] restrição extra: o programa deve ser capaz de lidar com inter

rupcoes de sinal (como ctrl+c), garantindo que os arquivos sejam fechados e o status de consistencia seja atualizado para '1' (inconsistente) antes da finalizacao forcada. [9] a implementacao deve ser realizada usando a linguagem de programação c . a

s funções das bibliotecas <stdio.h> devem ser utilizadas para operações relacionadas à escrita e leitura dos arquivos . a implementação não pode ser feita em qualquer outra linguagem de programação . o programa executará no [run.codes]. fundamentação

 teórica conceitos e características dos diversos métodos para representar os conceitos de campo e de registro em um arquivo de dados podem ser encontrados nos slides de sala de aula e também no livro file structures (second edition), de michael j. f

olk e bill zoellick. material para entregar arquivo compactado (a ser entregue no run.codes). deve ser preparado um arquivo.tar.gz (em vez de .zip) contendo: · código fonte do programa devidamente documentado com doxygen. · arquivo de configuracao do

 doxygen (doxyfile). vídeo (a ser entregue no e-disciplinas). um vídeo gravado pelos integrantes do grupo, o qual deve ter, no máximo, 3 minutos de gravação (em vez de 5) . o vídeo deve explicar o trabalho desenvolvido . ou seja, o grupo deve apresen

tar: cada funcionalidade e uma breve descrição de como a funcionalidade foi implementada . todos os integrantes do grupo devem participar do video, sendo que o tempo de apresentação dos integrantes deve ser balanceado . ou seja, o tempo de participaç

ão de cada integrante deve ser aproximadamente o mesmo . o uso da webcam é opcional (em vez de obrigatorio).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de cienci

as matematicas e de computacao departamento de ciencias de computacao
instrucoes para fazer o script de compilacao. no [run.codes], em vez de utilizar um makefile tradicional, voce deve fornecer um script em shell chamado "build.sh" . a diretiva prin

cipal deve garantir que a compilacao otimize o codigo para execucao em sistemas de 64 bits . adicionalmente, para utilizar a funcao binarionatela, e necessario utilizar a flag -static para garantir que todas as dependencias sejam incluidas no binario

 final.
assim, a forma mais simples de se fazer o script de automacao e:
#!/bin/bash gcc -o executorprojeto *.c -static -lm ./executorprojeto
lembrando que o uso de *.c e obrigatorio para incluir todos os modulos desenvolvidos . adicionalmente, certi
fique-se de que o arquivo build.sh tenha permissoes de execucao (chmod +x), caso contrario o ambiente de correcao manual nao conseguira iniciar os testes.
instrucoes de entrega. o programa deve ser submetido via [run.codes]: · pagina: https://runcode

s.icmc.usp.br/ · segunda feira: codigo de matricula: ALFA9 · terca feira: codigo de matricula: BETA2
o video gravado deve ser submetido por meio de um servico de nuvem (google drive ou dropbox) e o link deve ser enviado via e-disciplinas, no qual o g

rupo vai informar o nome de cada integrante, o numero do grupo e o link de acesso . ao submeter o link, certifique-se de que as permissoes de visualizacao estao abertas para "qualquer pessoa com o link" . links que exigirem solicitacao de acesso ou q

ue apresentarem erro de 404 receberao nota zero imediatamente.
criterio de correcao criterio de avaliacao do trabalho. na correcao do trabalho, serao ponderados os seguintes aspectos.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
· corretude da execucao do programa. · atendimento as novas especificacoes do registro de cabecalho de 2
5 bytes e dos registros de dados variaveis de ate 120 bytes. · atendimento as especificacoes da sintaxe flexivel dos comandos de cada funcionalidade e do formato de saida com delimitadores pipe (|). · qualidade da documentacao doxygen entregue. a doc

umentacao interna tera um peso consideravel no trabalho. · estruturacao da solucao. o projeto deve apresentar uma organizacao adequada de arquivos e diretorios. · centralizacao do codigo. trechos de codigo que aparecem repetidamente podem ser mantido

s de forma linear para evitar a fragmentacao por excesso de funcoes. · uso de ferramentas de inteligencia artificial. o uso dessas ferramentas e permitido exclusivamente para a geracao de casos de teste e documentacao, mas proibido para a logica das

funcionalidades . o uso indevido acarretara desconto rigoroso na nota. video. integrantes que nao participarem da apresentacao receberao nota 0 no trabalho correspondente. casos de teste no [run.codes]. juntamente com a especificacao do trabalho, ser

UNIVERSIDADE DE SÃO PAULO
INSTITUTO DE CIÊNCIAS MATEMÁTICAS E DE COMPUTAÇÃO
Departamento de Ciências de Computação
Disciplina de Organização de Arquivos (SCC0215)
antos Pires · gustavo.rspires@usp.br ou telegram: @darrocaxd
Docente Profa. Dra. Cristina Dutra de Aguiar cdac@icmc.usp.br
João Gabriel Pieroli da Silva · joagabrielpieroli@usp.br ou telegram: @bielcomp24
Monitores
Pedro Lunkes Villela · pedrolunkesvillela@usp.br ou telegram: @pedrolunkes
Gustavo Ramos S
Renan Banci Catarin · renanbcata
rin@usp.br ou telegram: @Reckat
Renan Trofino Silva · renan.trofino@usp.br ou telegram: @renan823
Vinícius Souza Freitas · vininicius@usp.br ou telegram: @Vininicius
Trabalho Introdutório
ntrada e gerar um arquivo binário com esses dados, bem como realizar operações de busca, remoção e atualização. Ele é um trabalho introdutório, de forma que será usado como base para o desenvolvimento de todos os demais trabalhos da disciplina.
Este trabalho tem como objetivo obter dados de um arquivo de e
O tra

balho deve ser feito individualmente ou em trios (3 alunos) da mesma turma. A solução deve ser proposta exclusivamente pelos alunos com base nos conhecimentos adquiridos nas aulas. Consulte as notas de aula e o livro texto quando necessário.
Fundamen

tos da disciplina de Bases de Dados
A disciplina de Organização de Arquivos é uma disciplina fundamental para a disciplina de Bases de Dados. A definição dos trabalhos práticos é feita considerando esse aspecto, ou seja, os trabalhos são especificado

s em termos de várias funcionalidades, e essas funcionalidades são relacionadas tanto com desafios enfrentados no mercado de trabalho quanto com as funcionalidades da linguagem SQL (Structured Query Language), que é a linguagem utilizada por sistemas

 gerenciadores.
Av. Trabalhador São-carlense, 400 centro. São Carlos - SP cep 13566-590. Brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao de banco de dados (sgbd

s) relacionais. as caracteristicas e o detalhamento de sql serao aprendidos na disciplina de bases de dados . porem, por meio do desenvolvimento deste trabalho pratico, os alunos podem entrar em contato com alguns comandos da linguagem sql e verifica

r como eles sao implementados . os trabalhos práticos têm como objetivo armazenar e recuperar dados relacionados às estações e linhas do metrô e da cptm (companhia paulista de trens metropolitanos) da região metropolitana da cidade de são paulo (sp)

. um exemplo de uso desses dados é: "eu preciso pegar uma linha de metrô para ir para o aeroporto de guarulhos" . os dados manipulados indicam o trajeto que deve ser feito . em detalhes, os dados se referem às estações, às linhas, às distâncias entre

 as estações e aos trajetos . na disciplina de bases de dados, é ensinado que esses dados devem ser armazenados em arquivos separados, respeitando a normalização . entretanto, para aumentar a complexidade de gerencimento da redundancia nos trabalhos

da disciplina de organização de arquivos, todos os dados serão armazenados em tres arquivos distintos . isso significa que existe redundância dos dados, ou seja, o mesmo valor de dados é armazenado mais do que uma vez . descrição do arquivo de dados

. um arquivo de dados possui um registro de cabeçalho e 0 ou mais registros de dados . a descrição do registro de cabeçalho é feita conforme a definição a seguir . registro de cabeçalho. o registro de cabeçalho deve conter os seguintes campos: · stat

us: indica a consistência do arquivo de dados, devido à queda de energia, travamento do programa, etc. pode assumir os valores '1', para indicar que o arquivo de dados está inconsistente, ou '0', para indicar que o arquivo de dados está consistente .

 ao se abrir um arquivo para escrita, seu status deve ser '1' e, ao finalizar o uso desse arquivo, seu status deve ser '0' - tamanho: string de 1 byte. · topo: armazena o byte offset de um registro logicamente removido, ou 0 caso não haja registros l

ogicamente removidos - tamanho: inteiro de 4 bytes . av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias

 de computacao · proxrrn: armazena o valor do proximo rrn disponivel. deve ser iniciado com o valor '1' e deve ser alterado sempre que necessario tamanho: inteiro de 4 bytes. · nroestacoes: indica a quantidade de estacoes diferentes que estao armazen

adas no arquivo de dados . note que, se duas ou mais estacoes têm o mesmo nome, elas sao consideradas estacoes distintas - tamanho: inteiro de 4 bytes. · nroparesestacao: indica a quantidade de pares (codestacao, codproxestacao) diferentes que estao

armazenados no arquivo de dados tamanho: inteiro de 4 bytes. representacao grafica do registro de cabecalho. o tamanho do registro de cabecalho deve ser de 25 bytes, representado da seguinte forma: "0", "1", "2 3 4 5", "6 7 8 9", "10 11 12 13", "14 1

5 16 17 18 19 20 21", "22 23 24" "status", , "topo", , "proxrrn", , "nroestacoes", , "nro pares estacao" observacoes importantes. · o registro de cabecalho deve seguir estritamente a ordem definida na sua representacao grafica. · os campos sao de tam

anho variavel com delimitadores. portanto, os valores que forem armazenados devem ser finalizados por '|'. · neste projeto, o conceito de pagina de disco deve ser obrigatoriamente considerado para o calculo de offsets. registros de dados. os registro

s de dados sao de tamanho variavel, com campos de tamanho fixo e campos de tamanho variavel . para os campos de tamanho variavel, deve ser usado o metodo de delimitador de campo . os campos de tamanho fixo sao definidos da seguinte forma: · codestaca

o: codigo da estacao - inteiro - tamanho: 4 bytes. · codlinha: codigo da linha - inteiro - tamanho: 4 bytes. · codproxestacao: codigo da proxima estacao - inteiro - tamanho: 4 bytes. · distproxestacao: distancia para a proxima estacao - inteiro - tam

anho: 4 bytes. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp sao carlos scc universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao

 codlinhaintegra: codigo da linha que faz a integracao entre as linhas inteiro tamanho: 8 bytes · codestintegra: codigo da estacao que faz a integracao entre as linhas - inteiro tamanho: 8 bytes os campos de tamanho variavel sao definidos da seguinte

 forma: · nomeestacao: nome da estacao nomelinha: nome da linha adicionalmente, os seguintes campos de tamanho fixo tambem compoem cada registro. esses campos sao necessarios para o gerenciamento de registros logicamente removidos e para oferecer sup

orte para o metodo de delimitadores de campo. removido: indica se o registro esta logicamente removido. pode assumir os valores '0', para indicar que o registro esta marcado como logicamente removido, ou '1', para indicar que o registro nao esta marc

ado como removido. tamanho: string de 1 byte. proximo: armazena o byte offset do proximo registro logicamente removido tamanho: inteiro de 8 bytes. deve ser inicializado com o valor 0 quando necessario. os dados sao fornecidos juntamente com a especi

ficacao deste trabalho pratico por meio de um arquivo .json, sendo que sua especificacao esta disponivel na pagina da disciplina. no arquivo .json, o separador de campos e a chave do objeto e o primeiro registro nao especifica metadados. adicionalmen

te, campos nulos sao representados pela string "empty". representacao grafica dos registros de dados. o tamanho dos registros de dados deve ser variavel, com um limite maximo de 120 bytes, representado da seguinte forma: av. trabalhador são-carlense,

 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp 88 são carlos scc universidade de são paulo instituto de ciências matemáticas e de computação departamento de ciências de computação
representação gráfica dos registros de d
ados. o tamanho dos registros de dados deve ser variável até 120 bytes, representado da seguinte forma:
"0", "1", "9 10 11 12 13 14 15 16", "17 18 19 20", "21 22 23 24", "25 26 27 28" "removido", , "próximo (offset)", , "codestacao", , "codlinha", ,

"codproxestacao"
"29 30 31 32", "33 34 35 36 37 38 39 40", "41 42 43 44 45 46 47 48", "49...", "...119" "distproxestacao", , "codlinhaintegra", , "codestintegra", , "nomeestacao|", , "nomelinha|"
observações importantes. · cada registro de dados deve

 seguir estritamente a ordem definida na sua representação gráfica. · as strings de tamanho variável são identificadas por um delimitador pipe (|) e, portanto, devem ser finalizadas com este caractere. · os campos codestacao e nomeestacao aceitam val

ores nulos. os demais campos são de preenchimento obrigatório e não aceitam valores nulos. o arquivo .json com os dados de entrada já garante essa característica. · para os campos de tamanho fixo, os valores nulos devem ser representados pelo valor 0

. · para os campos de tamanho variável, armazenar um valor nulo significa armazenar a string "empty" seguida do delimitador. · deve ser feita a diferenciação entre o espaço utilizado e o lixo. sempre que houver lixo, ele deve ser identificado pelo ca

ractere '#'. nenhum byte do registro deve permanecer vazio, ou seja, cada byte deve armazenar um valor válido ou '#'. · não existe a necessidade de truncamento dos dados. o arquivo .json com os dados de entrada já garante essa característica. · neste

 projeto, o conceito de página de disco deve ser obrigatoriamente considerado.
programa descrição geral. implemente um programa em c por meio do qual o usuário possa obter dados de um arquivo de entrada e gerar arquivos binários com esses dados, bem

como realizar operações de busca nesses arquivos binários.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ci
encias de computacao importante. a definicao da sintaxe de cada comando bem como sua saida devem seguir com flexibilidade as especificacoes definidas em cada funcionalidade, desde que a logica de negocio seja mantida . para especificar a sintaxe de e

xecucucao, considere que o programa seja chamado de "executorprojeto" . essas orientacoes devem ser seguidas com cautela, uma vez que a avaliacao do funcionamento do programa sera realizada de forma manual pelos monitores . de forma geral, a ultima e

ntrada da entrada padrao e sempre o identificador de suas funcionalidades, conforme especificado a seguir . centralizacao. e importante manter o codigo em blocos extensos para evitar a fragmentacao excessiva do programa. trechos de programa que apare

cerem varias vezes podem ser repetidos para facilitar a leitura linear do fluxo . descricao especifica. o programa deve oferecer as seguintes funcionalidades : na linguagem sql, o comando create table e usado para criar uma tabela, a qual e implement

ada como um arquivo . geralmente, uma tabela possui um nome (que corresponde ao nome do arquivo) e varias colunas, as quais correspondem aos campos dos registros do arquivo de dados . a funcionalidade [1] representa um exemplo de implementacao do com

ando create table. [1] permita a leitura de varios registros obtidos a partir de um arquivo de entrada no formato json e a gravacao desses registros em tres arquivos de dados de saida . o arquivo de entrada no formato json e fornecido juntamente com

a especificacao do projeto, enquanto os arquivos de dados de saida devem ser gerados de acordo com as novas especificacoes deste trabalho pratico . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibiliz

ada na pagina do projeto da disciplina, para validar a integridade previa do ambiente . a funcao binarionatela deve ser usada antes que o arquivo seja aberto para escrita. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. bras

il www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [1]:
3.bin 1
arquivoentrada.json arquivosaida1.bin arquivosaida2.bin arquivosaida
onde:
arquivoentrada.json e um arquivo .json que contem os valores dos campos dos registros a serem armazenados nos arquivos binarios . arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios gerados conforme as nova

s especificacoes descritas neste trabalho pratico. 1 e o identificador da funcionalidade, agora inserido ao final da linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de saida no formato binario usando a funcao f

ornecida binarionatela antes de abrir os arquivos para escrita.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
ela antes de iniciar a funcionalidade, para validar a integridade previa do ambiente.
./executorprojeto estacao.json est1.bin est2.bin est3.bin 1
na linguagem sql, o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select. o comando mais basico consist
usar a funcao binarionat

e em especificar as clausulas select e from, da seguinte forma:
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos)
a funcionalidade [2] representa um exemplo de implementacao do

comando select . como todos os registros devem ser recuperados nessa funcionalidade, sua implementacao consiste em percorrer o arquivo de tras para frente (do ultimo registro para o primeiro).
[2] permita a recuperacao dos dados de todos os registros

 armazenados nos tres arquivos de dados de entrada, mostrando os dados de forma desorganizada e aleatoria na saida padrao para dificultar a leitura automatizada . o tratamento de 'lixo' deve ser ignorado, exibindo os caracteres '#' conforme aparecem

no disco . registros marcados como logicamente removidos (valor '0') devem ser exibidos com destaque.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias mat
ematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [2]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin 2
onde:
rios gerados conforme as especificacoes descritas neste trabalho pratico.
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos bina
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem ser mostrados de forma sequencial separados por um p

ipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos da seguinte forma: ao inves de exibir o valor 0, escreva VOID . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos da seguinte forma: EMPTY . a ordem

 de exibicao dos campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao existam registros:

arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
l 1 Parada Inglesa 2
exemplo de execucao (e mostrado um exemplo ilustrativo):
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bin 2 NULO NULO 992 2 Azul 1 Tucuruvi 1 55 4 1057 3 Azu
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
conforme visto na
 funcionalidade [2], na linguagem sql o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select . alem das clausulas select e from, outra clausula muito comum e a clausula where, que permite q

ue seja definido um criterio de busca sobre um ou mais campos, o qual e nomeado como criterio de selecao.
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos) where criterio de sel

ecao (ou seja, criterio de busca)
a funcionalidade [3] representa um exemplo de implementacao do comando select considerando a clausula where . como não existe indice definido sobre os campos dos registros, a implementacao dessa funcionalidade consis

te em percorrer o arquivo de tras para frente (da ultima pagina para a primeira).
[3] permita a recuperacao dos dados de todos os registros dos tres arquivos de dados de entrada, de forma que esses registros satisfacam qualquer um dos criterios de bu

sca (logica or) determinados pelo usuario . qualquer campo pode ser utilizado como forma de busca . adicionalmente, a busca deve ser feita considerando um ou mais campos . por exemplo, e possivel realizar a busca considerando somente o campo codestac

ao ou considerando os campos nomeestacao e nomelinha.
esta funcionalidade pode retornar 0 registros (quando nenhum satisfaz ao criterio de busca), 1 registro (quando apenas um satisfaz ao criterio de busca), ou varios registros . os valores dos campo

s do tipo string devem ser especificados entre aspas simples ('). para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . para a busca por valores nulos, d

eve-se especificar o valor void ou empty . registros marcados como logicamente removidos (status '0') devem ser exibidos obrigatoriamente . os tres arquivos de dados de entrada devem ser percorridos simultaneamente de forma decrescente.
av. trabalhad

or são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
sintaxe do comando para a funcionalidade [3]:
arquiv
osaida1.bin arquivosaida2.bin arquivosaida3.bin n 3
m1 nomecampo valorcampo1 nomecampomi valorcampoml m2 nomecampo valorcampo1 nomecampom2 valorcampom2 mn nomecampo valorcampo nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arqu
ivosaida3.bin sao os arquivos binarios de um determinado tipo, os quais foram gerados conforme as novas especificacoes descritas neste trabalho pratico . n e a quantidade de vezes que a busca deve acontecer . m e a quantidade de vezes que o par nome

do campo e valor do campo pode repetir em uma busca . o identificador da funcionalidade '3' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre nomecampo e valorcampo . os valores dos campos do tipo

 string devem ser especificados entre aspas simples (') . buscas por valores nulos devem ser especificadas com void ou empty.
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem

ser mostrados de forma sequencial separados por um pipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos como void . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos como empty . a ordem de exibicao d

os campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao seja encontrado o registro que c

ontem o valor do campo ou o campo pertence a um registro que esteja ativo (nao removido):
arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
n 1 3 1 nomeestacao 'luz' nulo nulo nulo 112 7 rubi luz 111 19 1257 56 4 amarela luz 55 55 4 nulo 10 1 azul luz 9
exemplo de execucao:
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bi
universidade de sao paulo instituto de

ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando delete e usado para remover dados em uma tabela . para tanto, devem ser especificados quais dados (ou seja, registros) devem ser removidos, de aco

rdo com algum criterio.
delete from tabela (ou seja, arquivo que contem os campos) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [4] representa um exemplo de implementacao do comando delete.
[4] permita a remocao logica de r
egistros de tres arquivos de dados de entrada, baseado na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos. a implementacao dessa funcionalidade deve ser realizada usando o conceito de fila (fifo) de registros

logicamente removidos, e deve seguir com flexibilidade a materia apresentada em sala de aula . os registros a serem removidos devem ser aqueles que satisfaçam qualquer um dos criterios de busca (logica or) determinados pelo usuario, sendo que a busca

 deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de remocao . ao se remover um registro, os valores dos bytes referentes aos campos ja armazenados no registro devem ser so

brescritos pelo caractere '#', com exceção dos valores dos campos relacionados ao tratamento da lista encadeada . a funcionalidade [4] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito,

ou seja, caso a solicitacao do usuario nao retorne nenhum registro a ser removido, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionat

ela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo inst
ituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [4]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 4
m1 nomecampo valorcampo1 m2 nomecampo valorcampo1 mn nomecam
po valorcampo nomecampomi valorcampomi nomecampom2 valorcampom2 nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho

pratico introdutorio . as remocoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de remocoes a serem realizadas . m e a quantidade de vezes que o par nome do campo e valor do campo pode repeti

r na busca pelos registros a serem removidos . o identificador da funcionalidade '4' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre o nome do campo e o valor do campo . os valores dos campos do

 tipo string devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
men
sagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 4 1 nomeestacao 'luz' 2 nomelinha 'verde'; codproxest 27
execucao da funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as remocoes.
usar a funcao binarionatela antes de iniciar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando insert into e usado para inserir dados em uma tabela . para tanto, devem ser especificados os valores a ser

em armazenados em cada coluna da tabela, de acordo com o tipo de dado definido . a funcionalidade [5] representa um exemplo de implementacao do comando insert into.
[5] permita a insercao de novos registros em tres arquivos de dados de entrada, basea

do na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e inserindo novos dados obrigatoriamente no final do arquivo, segui

ndo com flexibilidade a materia apresentada em sala de aula . o lixo que permanece no registro deve ser identificado pelo caractere '#' . na entrada da funcionalidade [5], os dados sao referentes aos seguintes campos, na ordem inversa: codestintegra,

 codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao.
campos com valores nulos, na entrada da funcionalidade, devem ser identificados com void ou empty . os valores dos campos do tipo string devem ser especi

ficados entre aspas simples (') . para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . a funcionalidade [5] deve ser executada n vezes seguidas . antes

de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são c

arlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [5]:
arquivosaida1.bin arquivosaida2.bin arq
uivosaida3.bin n 5
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao nomelinha codlinha, nomeestacao, codestacao
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao, nomelinha codlinha, nomeestacao, codestacao
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdutorio. as insercoes a serem realizadas nessa funcionalidade devem ser feitas obrig

atoriamente no final de cada um desses arquivos, desprezando qualquer espaco logicamente removido.
n e o numero de insercoes a serem realizadas. para cada insercao, deve ser informado os valores a serem inseridos nos arquivos, considerando os seguint

es campos, na ordem inversa: codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao. o identificador da funcionalidade '5' deve ser inserido ao final da primeira linha de comando.
valores nulos d

evem ser identificados, na entrada da funcionalidade, por void ou empty. cada uma das n insercoes deve ser especificada em uma linha diferente. deve ser deixado um ponto e virgula (;) entre os valores dos campos. os valores dos campos do tipo string

devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
mensagem de said
a caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 5 void; void; void; void; 'branca'; 10; 'teste'; 500 void; void; void; void; 'branca'; 10; 'nova estacao'; 501
 funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as insercoes.
usar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando update e usado para atualizar dados em uma tabela . para tanto, devem ser esp

ecificados quais valores de dados de quais campos devem ser atualizados, de acordo com algum criterio de busca dos registros a serem atualizados.
update tabela (ou seja, arquivo que contem os dados) set quais colunas e quais valores (ou seja, quais c

ampos e seus valores) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [6] representa um exemplo de implementacao do comando update.
[6] permita a atualizacao de registros de tres arquivos de dados de entrada, baseado na aborda

gem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e deve seguir com flexibilidade a materia apresentada em sala de aula . desde q

ue os registros do arquivo de dados sao de tamanho variavel (com limite de 120 bytes), se a atualizacao resultar em um registro maior que o espaco original, o registro atual deve ser marcado como removido e a nova versao deve ser inserida obrigatoria

mente no final do arquivo . o lixo que porventura permanecer no registro atualizado deve ser identificado pelo caractere '#'.
os registros a serem atualizados devem ser aqueles que satisfacam qualquer um dos criterios de busca (logica or) determinado

s pelo usuario, sendo que a busca deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de atualizacao . adicionalmente, o campo utilizado como busca nao precisa ser, necessaria

mente, o campo a ser atualizado . por exemplo, pode-se buscar pelo campo codestacao, e pode-se atualizar o campo nomelinha . campos a serem atualizados com valores nulos devem ser identificados, na entrada da funcionalidade, com void ou empty . a fun

cionalidade [6] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcio

nalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasi

l www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [6]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 6
b; valorcampob1; nomecampobmi; valorcampobm1 pl nomecampoa; valorcampoa nomecampoap1; valorcampoapi m2 nomecampob2; valorcampob2 nomecampobm2; valorcampobm2 p2 nomecampoa; valorcampoa nomecampoap2; valorcampoap2 mn nomecampobn; valorcampob nomecampob
ml nomecampo

mn; valorcampobmn pn nomecampoa; valorcampoan nomecampoapn; valorcampoapn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdu

torio . as atualizacoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de atualizacoes a serem realizadas . m e a quantidade de vezes que o par nomecampob (campo de busca) e valorcampob (valor

de busca) pode repetir para filtrar os registros, utilizando a logica or . deve ser deixado um ponto e virgula (;) entre nomecampob e valorcampob . os valores dos campos do tipo string devem ser especificados entre aspas simples (') . p e a quantidad

e de vezes que o par nomecampoa (campo a ser atualizado) e valorcampoa (novo valor) pode repetir . deve ser deixado um ponto e virgula (;) entre nomecampoa e valorcampoa . os valores das strings a serem atualizadas devem estar entre aspas simples (')

 . o identificador da funcionalidade '6' deve ser inserido ao final da primeira linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de inici

ar a execucao da funcionalidade.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
linhaintegra; 4; codestacaointegra; 55 1 codestacao; 15 1 nomeestacao; 'exemplo'
./executorprojeto est1.bin est2.bin est3.bin 2 6 2 codestacao; 1; nomeestacao; 'tucuruvi' 3 codproxestacao; 15; cod
usar a funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados f

rente as atualizacoes.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
restricoes
guintes restricoes tem que ser garantidas no desenvolvimento do trabalho:
as se
[1] o arquivo de dados deve ser gravado em disco no modo binario . o modo texto nao pode ser usado.
[2] os dados do registro descrevem os nomes dos campos, os quais nao podem s

er alterados . ademais, todos os campos devem estar presentes na implementacao, e nenhum campo adicional pode ser incluido . o tamanho e a ordem de cada campo deve obrigatoriamente seguir a nova especificacao proposta.
[3] deve haver a manipulacao de

 valores nulos, utilizando obrigatoriamente as strings "void" e "empty" e o valor numerico 0, conforme as instrucoes definidas.
[4] e necessario realizar o tratamento de truncamento de dados caso o registro atualizado exceda o limite de 120 bytes.
[5

] devem ser exibidos avisos ou mensagens de erro de acordo com a especificacao flexivel de cada funcionalidade.
[6] os dados devem ser obrigatoriamente escritos registro a registro (utilizando structs completas) . ou seja, nao e possivel escrever os

dados campo a campo . essa restricao refere-se a entrada/saida, ou seja, a forma como os dados sao escritos no arquivo.
[7] o(s) aluno(s) que desenvolveu(desenvolveram) o trabalho pratico deve(m) constar como comentario no inicio do codigo (i.e. nusp

 e nome do aluno) . para trabalhos desenvolvidos por mais do que um aluno, nao sera atribuida nota ao aluno cujos dados nao constarem no codigo fonte.
[8] todo codigo fonte deve ser documentado utilizando o padrao doxygen . a documentacao interna inc

lui a documentacao de procedimentos, de funcoes, de variaveis, de partes do codigo fonte que realizam tarefas especificas . ou seja, o codigo fonte deve ser documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais.
[9] r

estrição extra: o programa deve implementar um sistema de log que registre cada operacao de escrita realizada nos arquivos binarios em um arquivo de texto separado chamado "operacoes.log".
[10] restrição extra: o uso de memoria ram deve ser otimizado

 para que o programa nunca mantenha mais de 100 registros carregados simultaneamente, utilizando tecnicas de busca em disco (fseek).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao
paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais. [11] restrição extra: todos os ponteiros utilizados para manipulaca

o de arquivos e memoria devem ser validados imediatamente apos a declaracao, garantindo que nao haja vazamento de memoria (memory leaks) sob pena de desconsideracao da funcionalidade. [12] restrição extra: o programa deve ser capaz de lidar com inter

rupcoes de sinal (como ctrl+c), garantindo que os arquivos sejam fechados e o status de consistencia seja atualizado para '1' (inconsistente) antes da finalizacao forcada. [9] a implementacao deve ser realizada usando a linguagem de programação c . a

s funções das bibliotecas <stdio.h> devem ser utilizadas para operações relacionadas à escrita e leitura dos arquivos . a implementação não pode ser feita em qualquer outra linguagem de programação . o programa executará no [run.codes]. fundamentação

 teórica conceitos e características dos diversos métodos para representar os conceitos de campo e de registro em um arquivo de dados podem ser encontrados nos slides de sala de aula e também no livro file structures (second edition), de michael j. f

olk e bill zoellick. material para entregar arquivo compactado (a ser entregue no run.codes). deve ser preparado um arquivo.tar.gz (em vez de .zip) contendo: · código fonte do programa devidamente documentado com doxygen. · arquivo de configuracao do

 doxygen (doxyfile). vídeo (a ser entregue no e-disciplinas). um vídeo gravado pelos integrantes do grupo, o qual deve ter, no máximo, 3 minutos de gravação (em vez de 5) . o vídeo deve explicar o trabalho desenvolvido . ou seja, o grupo deve apresen

tar: cada funcionalidade e uma breve descrição de como a funcionalidade foi implementada . todos os integrantes do grupo devem participar do video, sendo que o tempo de apresentação dos integrantes deve ser balanceado . ou seja, o tempo de participaç

ão de cada integrante deve ser aproximadamente o mesmo . o uso da webcam é opcional (em vez de obrigatorio).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de cienci

as matematicas e de computacao departamento de ciencias de computacao
instrucoes para fazer o script de compilacao. no [run.codes], em vez de utilizar um makefile tradicional, voce deve fornecer um script em shell chamado "build.sh" . a diretiva prin

cipal deve garantir que a compilacao otimize o codigo para execucao em sistemas de 64 bits . adicionalmente, para utilizar a funcao binarionatela, e necessario utilizar a flag -static para garantir que todas as dependencias sejam incluidas no binario

 final.
assim, a forma mais simples de se fazer o script de automacao e:
#!/bin/bash gcc -o executorprojeto *.c -static -lm ./executorprojeto
lembrando que o uso de *.c e obrigatorio para incluir todos os modulos desenvolvidos . adicionalmente, certi
fique-se de que o arquivo build.sh tenha permissoes de execucao (chmod +x), caso contrario o ambiente de correcao manual nao conseguira iniciar os testes.
instrucoes de entrega. o programa deve ser submetido via [run.codes]: · pagina: https://runcode

s.icmc.usp.br/ · segunda feira: codigo de matricula: ALFA9 · terca feira: codigo de matricula: BETA2
o video gravado deve ser submetido por meio de um servico de nuvem (google drive ou dropbox) e o link deve ser enviado via e-disciplinas, no qual o g

rupo vai informar o nome de cada integrante, o numero do grupo e o link de acesso . ao submeter o link, certifique-se de que as permissoes de visualizacao estao abertas para "qualquer pessoa com o link" . links que exigirem solicitacao de acesso ou q

ue apresentarem erro de 404 receberao nota zero imediatamente.
criterio de correcao criterio de avaliacao do trabalho. na correcao do trabalho, serao ponderados os seguintes aspectos.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
· corretude da execucao do programa. · atendimento as novas especificacoes do registro de cabecalho de 2
5 bytes e dos registros de dados variaveis de ate 120 bytes. · atendimento as especificacoes da sintaxe flexivel dos comandos de cada funcionalidade e do formato de saida com delimitadores pipe (|). · qualidade da documentacao doxygen entregue. a doc

umentacao interna tera um peso consideravel no trabalho. · estruturacao da solucao. o projeto deve apresentar uma organizacao adequada de arquivos e diretorios. · centralizacao do codigo. trechos de codigo que aparecem repetidamente podem ser mantido

s de forma linear para evitar a fragmentacao por excesso de funcoes. · uso de ferramentas de inteligencia artificial. o uso dessas ferramentas e permitido exclusivamente para a geracao de casos de teste e documentacao, mas proibido para a logica das

funcionalidades . o uso indevido acarretara desconto rigoroso na nota. video. integrantes que nao participarem da apresentacao receberao nota 0 no trabalho correspondente. casos de teste no [run.codes]. juntamente com a especificacao do trabalho, ser

UNIVERSIDADE DE SÃO PAULO
INSTITUTO DE CIÊNCIAS MATEMÁTICAS E DE COMPUTAÇÃO
Departamento de Ciências de Computação
Disciplina de Organização de Arquivos (SCC0215)
antos Pires · gustavo.rspires@usp.br ou telegram: @darrocaxd
Docente Profa. Dra. Cristina Dutra de Aguiar cdac@icmc.usp.br
João Gabriel Pieroli da Silva · joagabrielpieroli@usp.br ou telegram: @bielcomp24
Monitores
Pedro Lunkes Villela · pedrolunkesvillela@usp.br ou telegram: @pedrolunkes
Gustavo Ramos S
Renan Banci Catarin · renanbcata
rin@usp.br ou telegram: @Reckat
Renan Trofino Silva · renan.trofino@usp.br ou telegram: @renan823
Vinícius Souza Freitas · vininicius@usp.br ou telegram: @Vininicius
Trabalho Introdutório
ntrada e gerar um arquivo binário com esses dados, bem como realizar operações de busca, remoção e atualização. Ele é um trabalho introdutório, de forma que será usado como base para o desenvolvimento de todos os demais trabalhos da disciplina.
Este trabalho tem como objetivo obter dados de um arquivo de e
O tra

balho deve ser feito individualmente ou em trios (3 alunos) da mesma turma. A solução deve ser proposta exclusivamente pelos alunos com base nos conhecimentos adquiridos nas aulas. Consulte as notas de aula e o livro texto quando necessário.
Fundamen

tos da disciplina de Bases de Dados
A disciplina de Organização de Arquivos é uma disciplina fundamental para a disciplina de Bases de Dados. A definição dos trabalhos práticos é feita considerando esse aspecto, ou seja, os trabalhos são especificado

s em termos de várias funcionalidades, e essas funcionalidades são relacionadas tanto com desafios enfrentados no mercado de trabalho quanto com as funcionalidades da linguagem SQL (Structured Query Language), que é a linguagem utilizada por sistemas

 gerenciadores.
Av. Trabalhador São-carlense, 400 centro. São Carlos - SP cep 13566-590. Brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao de banco de dados (sgbd

s) relacionais. as caracteristicas e o detalhamento de sql serao aprendidos na disciplina de bases de dados . porem, por meio do desenvolvimento deste trabalho pratico, os alunos podem entrar em contato com alguns comandos da linguagem sql e verifica

r como eles sao implementados . os trabalhos práticos têm como objetivo armazenar e recuperar dados relacionados às estações e linhas do metrô e da cptm (companhia paulista de trens metropolitanos) da região metropolitana da cidade de são paulo (sp)

. um exemplo de uso desses dados é: "eu preciso pegar uma linha de metrô para ir para o aeroporto de guarulhos" . os dados manipulados indicam o trajeto que deve ser feito . em detalhes, os dados se referem às estações, às linhas, às distâncias entre

 as estações e aos trajetos . na disciplina de bases de dados, é ensinado que esses dados devem ser armazenados em arquivos separados, respeitando a normalização . entretanto, para aumentar a complexidade de gerencimento da redundancia nos trabalhos

da disciplina de organização de arquivos, todos os dados serão armazenados em tres arquivos distintos . isso significa que existe redundância dos dados, ou seja, o mesmo valor de dados é armazenado mais do que uma vez . descrição do arquivo de dados

. um arquivo de dados possui um registro de cabeçalho e 0 ou mais registros de dados . a descrição do registro de cabeçalho é feita conforme a definição a seguir . registro de cabeçalho. o registro de cabeçalho deve conter os seguintes campos: · stat

us: indica a consistência do arquivo de dados, devido à queda de energia, travamento do programa, etc. pode assumir os valores '1', para indicar que o arquivo de dados está inconsistente, ou '0', para indicar que o arquivo de dados está consistente .

 ao se abrir um arquivo para escrita, seu status deve ser '1' e, ao finalizar o uso desse arquivo, seu status deve ser '0' - tamanho: string de 1 byte. · topo: armazena o byte offset de um registro logicamente removido, ou 0 caso não haja registros l

ogicamente removidos - tamanho: inteiro de 4 bytes . av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias

 de computacao · proxrrn: armazena o valor do proximo rrn disponivel. deve ser iniciado com o valor '1' e deve ser alterado sempre que necessario tamanho: inteiro de 4 bytes. · nroestacoes: indica a quantidade de estacoes diferentes que estao armazen

adas no arquivo de dados . note que, se duas ou mais estacoes têm o mesmo nome, elas sao consideradas estacoes distintas - tamanho: inteiro de 4 bytes. · nroparesestacao: indica a quantidade de pares (codestacao, codproxestacao) diferentes que estao

armazenados no arquivo de dados tamanho: inteiro de 4 bytes. representacao grafica do registro de cabecalho. o tamanho do registro de cabecalho deve ser de 25 bytes, representado da seguinte forma: "0", "1", "2 3 4 5", "6 7 8 9", "10 11 12 13", "14 1

5 16 17 18 19 20 21", "22 23 24" "status", , "topo", , "proxrrn", , "nroestacoes", , "nro pares estacao" observacoes importantes. · o registro de cabecalho deve seguir estritamente a ordem definida na sua representacao grafica. · os campos sao de tam

anho variavel com delimitadores. portanto, os valores que forem armazenados devem ser finalizados por '|'. · neste projeto, o conceito de pagina de disco deve ser obrigatoriamente considerado para o calculo de offsets. registros de dados. os registro

s de dados sao de tamanho variavel, com campos de tamanho fixo e campos de tamanho variavel . para os campos de tamanho variavel, deve ser usado o metodo de delimitador de campo . os campos de tamanho fixo sao definidos da seguinte forma: · codestaca

o: codigo da estacao - inteiro - tamanho: 4 bytes. · codlinha: codigo da linha - inteiro - tamanho: 4 bytes. · codproxestacao: codigo da proxima estacao - inteiro - tamanho: 4 bytes. · distproxestacao: distancia para a proxima estacao - inteiro - tam

anho: 4 bytes. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp sao carlos scc universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao

 codlinhaintegra: codigo da linha que faz a integracao entre as linhas inteiro tamanho: 8 bytes · codestintegra: codigo da estacao que faz a integracao entre as linhas - inteiro tamanho: 8 bytes os campos de tamanho variavel sao definidos da seguinte

 forma: · nomeestacao: nome da estacao nomelinha: nome da linha adicionalmente, os seguintes campos de tamanho fixo tambem compoem cada registro. esses campos sao necessarios para o gerenciamento de registros logicamente removidos e para oferecer sup

orte para o metodo de delimitadores de campo. removido: indica se o registro esta logicamente removido. pode assumir os valores '0', para indicar que o registro esta marcado como logicamente removido, ou '1', para indicar que o registro nao esta marc

ado como removido. tamanho: string de 1 byte. proximo: armazena o byte offset do proximo registro logicamente removido tamanho: inteiro de 8 bytes. deve ser inicializado com o valor 0 quando necessario. os dados sao fornecidos juntamente com a especi

ficacao deste trabalho pratico por meio de um arquivo .json, sendo que sua especificacao esta disponivel na pagina da disciplina. no arquivo .json, o separador de campos e a chave do objeto e o primeiro registro nao especifica metadados. adicionalmen

te, campos nulos sao representados pela string "empty". representacao grafica dos registros de dados. o tamanho dos registros de dados deve ser variavel, com um limite maximo de 120 bytes, representado da seguinte forma: av. trabalhador são-carlense,

 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp 88 são carlos scc universidade de são paulo instituto de ciências matemáticas e de computação departamento de ciências de computação
representação gráfica dos registros de d
ados. o tamanho dos registros de dados deve ser variável até 120 bytes, representado da seguinte forma:
"0", "1", "9 10 11 12 13 14 15 16", "17 18 19 20", "21 22 23 24", "25 26 27 28" "removido", , "próximo (offset)", , "codestacao", , "codlinha", ,

"codproxestacao"
"29 30 31 32", "33 34 35 36 37 38 39 40", "41 42 43 44 45 46 47 48", "49...", "...119" "distproxestacao", , "codlinhaintegra", , "codestintegra", , "nomeestacao|", , "nomelinha|"
observações importantes. · cada registro de dados deve

 seguir estritamente a ordem definida na sua representação gráfica. · as strings de tamanho variável são identificadas por um delimitador pipe (|) e, portanto, devem ser finalizadas com este caractere. · os campos codestacao e nomeestacao aceitam val

ores nulos. os demais campos são de preenchimento obrigatório e não aceitam valores nulos. o arquivo .json com os dados de entrada já garante essa característica. · para os campos de tamanho fixo, os valores nulos devem ser representados pelo valor 0

. · para os campos de tamanho variável, armazenar um valor nulo significa armazenar a string "empty" seguida do delimitador. · deve ser feita a diferenciação entre o espaço utilizado e o lixo. sempre que houver lixo, ele deve ser identificado pelo ca

ractere '#'. nenhum byte do registro deve permanecer vazio, ou seja, cada byte deve armazenar um valor válido ou '#'. · não existe a necessidade de truncamento dos dados. o arquivo .json com os dados de entrada já garante essa característica. · neste

 projeto, o conceito de página de disco deve ser obrigatoriamente considerado.
programa descrição geral. implemente um programa em c por meio do qual o usuário possa obter dados de um arquivo de entrada e gerar arquivos binários com esses dados, bem

como realizar operações de busca nesses arquivos binários.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ci
encias de computacao importante. a definicao da sintaxe de cada comando bem como sua saida devem seguir com flexibilidade as especificacoes definidas em cada funcionalidade, desde que a logica de negocio seja mantida . para especificar a sintaxe de e

xecucucao, considere que o programa seja chamado de "executorprojeto" . essas orientacoes devem ser seguidas com cautela, uma vez que a avaliacao do funcionamento do programa sera realizada de forma manual pelos monitores . de forma geral, a ultima e

ntrada da entrada padrao e sempre o identificador de suas funcionalidades, conforme especificado a seguir . centralizacao. e importante manter o codigo em blocos extensos para evitar a fragmentacao excessiva do programa. trechos de programa que apare

cerem varias vezes podem ser repetidos para facilitar a leitura linear do fluxo . descricao especifica. o programa deve oferecer as seguintes funcionalidades : na linguagem sql, o comando create table e usado para criar uma tabela, a qual e implement

ada como um arquivo . geralmente, uma tabela possui um nome (que corresponde ao nome do arquivo) e varias colunas, as quais correspondem aos campos dos registros do arquivo de dados . a funcionalidade [1] representa um exemplo de implementacao do com

ando create table. [1] permita a leitura de varios registros obtidos a partir de um arquivo de entrada no formato json e a gravacao desses registros em tres arquivos de dados de saida . o arquivo de entrada no formato json e fornecido juntamente com

a especificacao do projeto, enquanto os arquivos de dados de saida devem ser gerados de acordo com as novas especificacoes deste trabalho pratico . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibiliz

ada na pagina do projeto da disciplina, para validar a integridade previa do ambiente . a funcao binarionatela deve ser usada antes que o arquivo seja aberto para escrita. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. bras

il www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [1]:
3.bin 1
arquivoentrada.json arquivosaida1.bin arquivosaida2.bin arquivosaida
onde:
arquivoentrada.json e um arquivo .json que contem os valores dos campos dos registros a serem armazenados nos arquivos binarios . arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios gerados conforme as nova

s especificacoes descritas neste trabalho pratico. 1 e o identificador da funcionalidade, agora inserido ao final da linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de saida no formato binario usando a funcao f

ornecida binarionatela antes de abrir os arquivos para escrita.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
ela antes de iniciar a funcionalidade, para validar a integridade previa do ambiente.
./executorprojeto estacao.json est1.bin est2.bin est3.bin 1
na linguagem sql, o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select. o comando mais basico consist
usar a funcao binarionat

e em especificar as clausulas select e from, da seguinte forma:
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos)
a funcionalidade [2] representa um exemplo de implementacao do

comando select . como todos os registros devem ser recuperados nessa funcionalidade, sua implementacao consiste em percorrer o arquivo de tras para frente (do ultimo registro para o primeiro).
[2] permita a recuperacao dos dados de todos os registros

 armazenados nos tres arquivos de dados de entrada, mostrando os dados de forma desorganizada e aleatoria na saida padrao para dificultar a leitura automatizada . o tratamento de 'lixo' deve ser ignorado, exibindo os caracteres '#' conforme aparecem

no disco . registros marcados como logicamente removidos (valor '0') devem ser exibidos com destaque.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias mat
ematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [2]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin 2
onde:
rios gerados conforme as especificacoes descritas neste trabalho pratico.
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos bina
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem ser mostrados de forma sequencial separados por um p

ipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos da seguinte forma: ao inves de exibir o valor 0, escreva VOID . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos da seguinte forma: EMPTY . a ordem

 de exibicao dos campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao existam registros:

arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
l 1 Parada Inglesa 2
exemplo de execucao (e mostrado um exemplo ilustrativo):
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bin 2 NULO NULO 992 2 Azul 1 Tucuruvi 1 55 4 1057 3 Azu
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
conforme visto na
 funcionalidade [2], na linguagem sql o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select . alem das clausulas select e from, outra clausula muito comum e a clausula where, que permite q

ue seja definido um criterio de busca sobre um ou mais campos, o qual e nomeado como criterio de selecao.
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos) where criterio de sel

ecao (ou seja, criterio de busca)
a funcionalidade [3] representa um exemplo de implementacao do comando select considerando a clausula where . como não existe indice definido sobre os campos dos registros, a implementacao dessa funcionalidade consis

te em percorrer o arquivo de tras para frente (da ultima pagina para a primeira).
[3] permita a recuperacao dos dados de todos os registros dos tres arquivos de dados de entrada, de forma que esses registros satisfacam qualquer um dos criterios de bu

sca (logica or) determinados pelo usuario . qualquer campo pode ser utilizado como forma de busca . adicionalmente, a busca deve ser feita considerando um ou mais campos . por exemplo, e possivel realizar a busca considerando somente o campo codestac

ao ou considerando os campos nomeestacao e nomelinha.
esta funcionalidade pode retornar 0 registros (quando nenhum satisfaz ao criterio de busca), 1 registro (quando apenas um satisfaz ao criterio de busca), ou varios registros . os valores dos campo

s do tipo string devem ser especificados entre aspas simples ('). para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . para a busca por valores nulos, d

eve-se especificar o valor void ou empty . registros marcados como logicamente removidos (status '0') devem ser exibidos obrigatoriamente . os tres arquivos de dados de entrada devem ser percorridos simultaneamente de forma decrescente.
av. trabalhad

or são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
sintaxe do comando para a funcionalidade [3]:
arquiv
osaida1.bin arquivosaida2.bin arquivosaida3.bin n 3
m1 nomecampo valorcampo1 nomecampomi valorcampoml m2 nomecampo valorcampo1 nomecampom2 valorcampom2 mn nomecampo valorcampo nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arqu
ivosaida3.bin sao os arquivos binarios de um determinado tipo, os quais foram gerados conforme as novas especificacoes descritas neste trabalho pratico . n e a quantidade de vezes que a busca deve acontecer . m e a quantidade de vezes que o par nome

do campo e valor do campo pode repetir em uma busca . o identificador da funcionalidade '3' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre nomecampo e valorcampo . os valores dos campos do tipo

 string devem ser especificados entre aspas simples (') . buscas por valores nulos devem ser especificadas com void ou empty.
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem

ser mostrados de forma sequencial separados por um pipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos como void . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos como empty . a ordem de exibicao d

os campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao seja encontrado o registro que c

ontem o valor do campo ou o campo pertence a um registro que esteja ativo (nao removido):
arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
n 1 3 1 nomeestacao 'luz' nulo nulo nulo 112 7 rubi luz 111 19 1257 56 4 amarela luz 55 55 4 nulo 10 1 azul luz 9
exemplo de execucao:
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bi
universidade de sao paulo instituto de

ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando delete e usado para remover dados em uma tabela . para tanto, devem ser especificados quais dados (ou seja, registros) devem ser removidos, de aco

rdo com algum criterio.
delete from tabela (ou seja, arquivo que contem os campos) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [4] representa um exemplo de implementacao do comando delete.
[4] permita a remocao logica de r
egistros de tres arquivos de dados de entrada, baseado na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos. a implementacao dessa funcionalidade deve ser realizada usando o conceito de fila (fifo) de registros

logicamente removidos, e deve seguir com flexibilidade a materia apresentada em sala de aula . os registros a serem removidos devem ser aqueles que satisfaçam qualquer um dos criterios de busca (logica or) determinados pelo usuario, sendo que a busca

 deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de remocao . ao se remover um registro, os valores dos bytes referentes aos campos ja armazenados no registro devem ser so

brescritos pelo caractere '#', com exceção dos valores dos campos relacionados ao tratamento da lista encadeada . a funcionalidade [4] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito,

ou seja, caso a solicitacao do usuario nao retorne nenhum registro a ser removido, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionat

ela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo inst
ituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [4]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 4
m1 nomecampo valorcampo1 m2 nomecampo valorcampo1 mn nomecam
po valorcampo nomecampomi valorcampomi nomecampom2 valorcampom2 nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho

pratico introdutorio . as remocoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de remocoes a serem realizadas . m e a quantidade de vezes que o par nome do campo e valor do campo pode repeti

r na busca pelos registros a serem removidos . o identificador da funcionalidade '4' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre o nome do campo e o valor do campo . os valores dos campos do

 tipo string devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
men
sagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 4 1 nomeestacao 'luz' 2 nomelinha 'verde'; codproxest 27
execucao da funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as remocoes.
usar a funcao binarionatela antes de iniciar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando insert into e usado para inserir dados em uma tabela . para tanto, devem ser especificados os valores a ser

em armazenados em cada coluna da tabela, de acordo com o tipo de dado definido . a funcionalidade [5] representa um exemplo de implementacao do comando insert into.
[5] permita a insercao de novos registros em tres arquivos de dados de entrada, basea

do na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e inserindo novos dados obrigatoriamente no final do arquivo, segui

ndo com flexibilidade a materia apresentada em sala de aula . o lixo que permanece no registro deve ser identificado pelo caractere '#' . na entrada da funcionalidade [5], os dados sao referentes aos seguintes campos, na ordem inversa: codestintegra,

 codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao.
campos com valores nulos, na entrada da funcionalidade, devem ser identificados com void ou empty . os valores dos campos do tipo string devem ser especi

ficados entre aspas simples (') . para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . a funcionalidade [5] deve ser executada n vezes seguidas . antes

de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são c

arlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [5]:
arquivosaida1.bin arquivosaida2.bin arq
uivosaida3.bin n 5
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao nomelinha codlinha, nomeestacao, codestacao
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao, nomelinha codlinha, nomeestacao, codestacao
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdutorio. as insercoes a serem realizadas nessa funcionalidade devem ser feitas obrig

atoriamente no final de cada um desses arquivos, desprezando qualquer espaco logicamente removido.
n e o numero de insercoes a serem realizadas. para cada insercao, deve ser informado os valores a serem inseridos nos arquivos, considerando os seguint

es campos, na ordem inversa: codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao. o identificador da funcionalidade '5' deve ser inserido ao final da primeira linha de comando.
valores nulos d

evem ser identificados, na entrada da funcionalidade, por void ou empty. cada uma das n insercoes deve ser especificada em uma linha diferente. deve ser deixado um ponto e virgula (;) entre os valores dos campos. os valores dos campos do tipo string

devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
mensagem de said
a caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 5 void; void; void; void; 'branca'; 10; 'teste'; 500 void; void; void; void; 'branca'; 10; 'nova estacao'; 501
 funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as insercoes.
usar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando update e usado para atualizar dados em uma tabela . para tanto, devem ser esp

ecificados quais valores de dados de quais campos devem ser atualizados, de acordo com algum criterio de busca dos registros a serem atualizados.
update tabela (ou seja, arquivo que contem os dados) set quais colunas e quais valores (ou seja, quais c

ampos e seus valores) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [6] representa um exemplo de implementacao do comando update.
[6] permita a atualizacao de registros de tres arquivos de dados de entrada, baseado na aborda

gem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e deve seguir com flexibilidade a materia apresentada em sala de aula . desde q

ue os registros do arquivo de dados sao de tamanho variavel (com limite de 120 bytes), se a atualizacao resultar em um registro maior que o espaco original, o registro atual deve ser marcado como removido e a nova versao deve ser inserida obrigatoria

mente no final do arquivo . o lixo que porventura permanecer no registro atualizado deve ser identificado pelo caractere '#'.
os registros a serem atualizados devem ser aqueles que satisfacam qualquer um dos criterios de busca (logica or) determinado

s pelo usuario, sendo que a busca deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de atualizacao . adicionalmente, o campo utilizado como busca nao precisa ser, necessaria

mente, o campo a ser atualizado . por exemplo, pode-se buscar pelo campo codestacao, e pode-se atualizar o campo nomelinha . campos a serem atualizados com valores nulos devem ser identificados, na entrada da funcionalidade, com void ou empty . a fun

cionalidade [6] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcio

nalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasi

l www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [6]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 6
b; valorcampob1; nomecampobmi; valorcampobm1 pl nomecampoa; valorcampoa nomecampoap1; valorcampoapi m2 nomecampob2; valorcampob2 nomecampobm2; valorcampobm2 p2 nomecampoa; valorcampoa nomecampoap2; valorcampoap2 mn nomecampobn; valorcampob nomecampob
ml nomecampo

mn; valorcampobmn pn nomecampoa; valorcampoan nomecampoapn; valorcampoapn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdu

torio . as atualizacoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de atualizacoes a serem realizadas . m e a quantidade de vezes que o par nomecampob (campo de busca) e valorcampob (valor

de busca) pode repetir para filtrar os registros, utilizando a logica or . deve ser deixado um ponto e virgula (;) entre nomecampob e valorcampob . os valores dos campos do tipo string devem ser especificados entre aspas simples (') . p e a quantidad

e de vezes que o par nomecampoa (campo a ser atualizado) e valorcampoa (novo valor) pode repetir . deve ser deixado um ponto e virgula (;) entre nomecampoa e valorcampoa . os valores das strings a serem atualizadas devem estar entre aspas simples (')

 . o identificador da funcionalidade '6' deve ser inserido ao final da primeira linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de inici

ar a execucao da funcionalidade.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
linhaintegra; 4; codestacaointegra; 55 1 codestacao; 15 1 nomeestacao; 'exemplo'
./executorprojeto est1.bin est2.bin est3.bin 2 6 2 codestacao; 1; nomeestacao; 'tucuruvi' 3 codproxestacao; 15; cod
usar a funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados f

rente as atualizacoes.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
restricoes
guintes restricoes tem que ser garantidas no desenvolvimento do trabalho:
as se
[1] o arquivo de dados deve ser gravado em disco no modo binario . o modo texto nao pode ser usado.
[2] os dados do registro descrevem os nomes dos campos, os quais nao podem s

er alterados . ademais, todos os campos devem estar presentes na implementacao, e nenhum campo adicional pode ser incluido . o tamanho e a ordem de cada campo deve obrigatoriamente seguir a nova especificacao proposta.
[3] deve haver a manipulacao de

 valores nulos, utilizando obrigatoriamente as strings "void" e "empty" e o valor numerico 0, conforme as instrucoes definidas.
[4] e necessario realizar o tratamento de truncamento de dados caso o registro atualizado exceda o limite de 120 bytes.
[5

] devem ser exibidos avisos ou mensagens de erro de acordo com a especificacao flexivel de cada funcionalidade.
[6] os dados devem ser obrigatoriamente escritos registro a registro (utilizando structs completas) . ou seja, nao e possivel escrever os

dados campo a campo . essa restricao refere-se a entrada/saida, ou seja, a forma como os dados sao escritos no arquivo.
[7] o(s) aluno(s) que desenvolveu(desenvolveram) o trabalho pratico deve(m) constar como comentario no inicio do codigo (i.e. nusp

 e nome do aluno) . para trabalhos desenvolvidos por mais do que um aluno, nao sera atribuida nota ao aluno cujos dados nao constarem no codigo fonte.
[8] todo codigo fonte deve ser documentado utilizando o padrao doxygen . a documentacao interna inc

lui a documentacao de procedimentos, de funcoes, de variaveis, de partes do codigo fonte que realizam tarefas especificas . ou seja, o codigo fonte deve ser documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais.
[9] r

estrição extra: o programa deve implementar um sistema de log que registre cada operacao de escrita realizada nos arquivos binarios em um arquivo de texto separado chamado "operacoes.log".
[10] restrição extra: o uso de memoria ram deve ser otimizado

 para que o programa nunca mantenha mais de 100 registros carregados simultaneamente, utilizando tecnicas de busca em disco (fseek).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao
paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais. [11] restrição extra: todos os ponteiros utilizados para manipulaca

o de arquivos e memoria devem ser validados imediatamente apos a declaracao, garantindo que nao haja vazamento de memoria (memory leaks) sob pena de desconsideracao da funcionalidade. [12] restrição extra: o programa deve ser capaz de lidar com inter

rupcoes de sinal (como ctrl+c), garantindo que os arquivos sejam fechados e o status de consistencia seja atualizado para '1' (inconsistente) antes da finalizacao forcada. [9] a implementacao deve ser realizada usando a linguagem de programação c . a

s funções das bibliotecas <stdio.h> devem ser utilizadas para operações relacionadas à escrita e leitura dos arquivos . a implementação não pode ser feita em qualquer outra linguagem de programação . o programa executará no [run.codes]. fundamentação

 teórica conceitos e características dos diversos métodos para representar os conceitos de campo e de registro em um arquivo de dados podem ser encontrados nos slides de sala de aula e também no livro file structures (second edition), de michael j. f

olk e bill zoellick. material para entregar arquivo compactado (a ser entregue no run.codes). deve ser preparado um arquivo.tar.gz (em vez de .zip) contendo: · código fonte do programa devidamente documentado com doxygen. · arquivo de configuracao do

 doxygen (doxyfile). vídeo (a ser entregue no e-disciplinas). um vídeo gravado pelos integrantes do grupo, o qual deve ter, no máximo, 3 minutos de gravação (em vez de 5) . o vídeo deve explicar o trabalho desenvolvido . ou seja, o grupo deve apresen

tar: cada funcionalidade e uma breve descrição de como a funcionalidade foi implementada . todos os integrantes do grupo devem participar do video, sendo que o tempo de apresentação dos integrantes deve ser balanceado . ou seja, o tempo de participaç

ão de cada integrante deve ser aproximadamente o mesmo . o uso da webcam é opcional (em vez de obrigatorio).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de cienci

as matematicas e de computacao departamento de ciencias de computacao
instrucoes para fazer o script de compilacao. no [run.codes], em vez de utilizar um makefile tradicional, voce deve fornecer um script em shell chamado "build.sh" . a diretiva prin

cipal deve garantir que a compilacao otimize o codigo para execucao em sistemas de 64 bits . adicionalmente, para utilizar a funcao binarionatela, e necessario utilizar a flag -static para garantir que todas as dependencias sejam incluidas no binario

 final.
assim, a forma mais simples de se fazer o script de automacao e:
#!/bin/bash gcc -o executorprojeto *.c -static -lm ./executorprojeto
lembrando que o uso de *.c e obrigatorio para incluir todos os modulos desenvolvidos . adicionalmente, certi
fique-se de que o arquivo build.sh tenha permissoes de execucao (chmod +x), caso contrario o ambiente de correcao manual nao conseguira iniciar os testes.
instrucoes de entrega. o programa deve ser submetido via [run.codes]: · pagina: https://runcode

s.icmc.usp.br/ · segunda feira: codigo de matricula: ALFA9 · terca feira: codigo de matricula: BETA2
o video gravado deve ser submetido por meio de um servico de nuvem (google drive ou dropbox) e o link deve ser enviado via e-disciplinas, no qual o g

rupo vai informar o nome de cada integrante, o numero do grupo e o link de acesso . ao submeter o link, certifique-se de que as permissoes de visualizacao estao abertas para "qualquer pessoa com o link" . links que exigirem solicitacao de acesso ou q

ue apresentarem erro de 404 receberao nota zero imediatamente.
criterio de correcao criterio de avaliacao do trabalho. na correcao do trabalho, serao ponderados os seguintes aspectos.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
· corretude da execucao do programa. · atendimento as novas especificacoes do registro de cabecalho de 2
5 bytes e dos registros de dados variaveis de ate 120 bytes. · atendimento as especificacoes da sintaxe flexivel dos comandos de cada funcionalidade e do formato de saida com delimitadores pipe (|). · qualidade da documentacao doxygen entregue. a doc

umentacao interna tera um peso consideravel no trabalho. · estruturacao da solucao. o projeto deve apresentar uma organizacao adequada de arquivos e diretorios. · centralizacao do codigo. trechos de codigo que aparecem repetidamente podem ser mantido

s de forma linear para evitar a fragmentacao por excesso de funcoes. · uso de ferramentas de inteligencia artificial. o uso dessas ferramentas e permitido exclusivamente para a geracao de casos de teste e documentacao, mas proibido para a logica das

funcionalidades . o uso indevido acarretara desconto rigoroso na nota. video. integrantes que nao participarem da apresentacao receberao nota 0 no trabalho correspondente. casos de teste no [run.codes]. juntamente com a especificacao do trabalho, ser

UNIVERSIDADE DE SÃO PAULO
INSTITUTO DE CIÊNCIAS MATEMÁTICAS E DE COMPUTAÇÃO
Departamento de Ciências de Computação
Disciplina de Organização de Arquivos (SCC0215)
antos Pires · gustavo.rspires@usp.br ou telegram: @darrocaxd
Docente Profa. Dra. Cristina Dutra de Aguiar cdac@icmc.usp.br
João Gabriel Pieroli da Silva · joagabrielpieroli@usp.br ou telegram: @bielcomp24
Monitores
Pedro Lunkes Villela · pedrolunkesvillela@usp.br ou telegram: @pedrolunkes
Gustavo Ramos S
Renan Banci Catarin · renanbcata
rin@usp.br ou telegram: @Reckat
Renan Trofino Silva · renan.trofino@usp.br ou telegram: @renan823
Vinícius Souza Freitas · vininicius@usp.br ou telegram: @Vininicius
Trabalho Introdutório
ntrada e gerar um arquivo binário com esses dados, bem como realizar operações de busca, remoção e atualização. Ele é um trabalho introdutório, de forma que será usado como base para o desenvolvimento de todos os demais trabalhos da disciplina.
Este trabalho tem como objetivo obter dados de um arquivo de e
O tra

balho deve ser feito individualmente ou em trios (3 alunos) da mesma turma. A solução deve ser proposta exclusivamente pelos alunos com base nos conhecimentos adquiridos nas aulas. Consulte as notas de aula e o livro texto quando necessário.
Fundamen

tos da disciplina de Bases de Dados
A disciplina de Organização de Arquivos é uma disciplina fundamental para a disciplina de Bases de Dados. A definição dos trabalhos práticos é feita considerando esse aspecto, ou seja, os trabalhos são especificado

s em termos de várias funcionalidades, e essas funcionalidades são relacionadas tanto com desafios enfrentados no mercado de trabalho quanto com as funcionalidades da linguagem SQL (Structured Query Language), que é a linguagem utilizada por sistemas

 gerenciadores.
Av. Trabalhador São-carlense, 400 centro. São Carlos - SP cep 13566-590. Brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao de banco de dados (sgbd

s) relacionais. as caracteristicas e o detalhamento de sql serao aprendidos na disciplina de bases de dados . porem, por meio do desenvolvimento deste trabalho pratico, os alunos podem entrar em contato com alguns comandos da linguagem sql e verifica

r como eles sao implementados . os trabalhos práticos têm como objetivo armazenar e recuperar dados relacionados às estações e linhas do metrô e da cptm (companhia paulista de trens metropolitanos) da região metropolitana da cidade de são paulo (sp)

. um exemplo de uso desses dados é: "eu preciso pegar uma linha de metrô para ir para o aeroporto de guarulhos" . os dados manipulados indicam o trajeto que deve ser feito . em detalhes, os dados se referem às estações, às linhas, às distâncias entre

 as estações e aos trajetos . na disciplina de bases de dados, é ensinado que esses dados devem ser armazenados em arquivos separados, respeitando a normalização . entretanto, para aumentar a complexidade de gerencimento da redundancia nos trabalhos

da disciplina de organização de arquivos, todos os dados serão armazenados em tres arquivos distintos . isso significa que existe redundância dos dados, ou seja, o mesmo valor de dados é armazenado mais do que uma vez . descrição do arquivo de dados

. um arquivo de dados possui um registro de cabeçalho e 0 ou mais registros de dados . a descrição do registro de cabeçalho é feita conforme a definição a seguir . registro de cabeçalho. o registro de cabeçalho deve conter os seguintes campos: · stat

us: indica a consistência do arquivo de dados, devido à queda de energia, travamento do programa, etc. pode assumir os valores '1', para indicar que o arquivo de dados está inconsistente, ou '0', para indicar que o arquivo de dados está consistente .

 ao se abrir um arquivo para escrita, seu status deve ser '1' e, ao finalizar o uso desse arquivo, seu status deve ser '0' - tamanho: string de 1 byte. · topo: armazena o byte offset de um registro logicamente removido, ou 0 caso não haja registros l

ogicamente removidos - tamanho: inteiro de 4 bytes . av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias

 de computacao · proxrrn: armazena o valor do proximo rrn disponivel. deve ser iniciado com o valor '1' e deve ser alterado sempre que necessario tamanho: inteiro de 4 bytes. · nroestacoes: indica a quantidade de estacoes diferentes que estao armazen

adas no arquivo de dados . note que, se duas ou mais estacoes têm o mesmo nome, elas sao consideradas estacoes distintas - tamanho: inteiro de 4 bytes. · nroparesestacao: indica a quantidade de pares (codestacao, codproxestacao) diferentes que estao

armazenados no arquivo de dados tamanho: inteiro de 4 bytes. representacao grafica do registro de cabecalho. o tamanho do registro de cabecalho deve ser de 25 bytes, representado da seguinte forma: "0", "1", "2 3 4 5", "6 7 8 9", "10 11 12 13", "14 1

5 16 17 18 19 20 21", "22 23 24" "status", , "topo", , "proxrrn", , "nroestacoes", , "nro pares estacao" observacoes importantes. · o registro de cabecalho deve seguir estritamente a ordem definida na sua representacao grafica. · os campos sao de tam

anho variavel com delimitadores. portanto, os valores que forem armazenados devem ser finalizados por '|'. · neste projeto, o conceito de pagina de disco deve ser obrigatoriamente considerado para o calculo de offsets. registros de dados. os registro

s de dados sao de tamanho variavel, com campos de tamanho fixo e campos de tamanho variavel . para os campos de tamanho variavel, deve ser usado o metodo de delimitador de campo . os campos de tamanho fixo sao definidos da seguinte forma: · codestaca

o: codigo da estacao - inteiro - tamanho: 4 bytes. · codlinha: codigo da linha - inteiro - tamanho: 4 bytes. · codproxestacao: codigo da proxima estacao - inteiro - tamanho: 4 bytes. · distproxestacao: distancia para a proxima estacao - inteiro - tam

anho: 4 bytes. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp sao carlos scc universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao

 codlinhaintegra: codigo da linha que faz a integracao entre as linhas inteiro tamanho: 8 bytes · codestintegra: codigo da estacao que faz a integracao entre as linhas - inteiro tamanho: 8 bytes os campos de tamanho variavel sao definidos da seguinte

 forma: · nomeestacao: nome da estacao nomelinha: nome da linha adicionalmente, os seguintes campos de tamanho fixo tambem compoem cada registro. esses campos sao necessarios para o gerenciamento de registros logicamente removidos e para oferecer sup

orte para o metodo de delimitadores de campo. removido: indica se o registro esta logicamente removido. pode assumir os valores '0', para indicar que o registro esta marcado como logicamente removido, ou '1', para indicar que o registro nao esta marc

ado como removido. tamanho: string de 1 byte. proximo: armazena o byte offset do proximo registro logicamente removido tamanho: inteiro de 8 bytes. deve ser inicializado com o valor 0 quando necessario. os dados sao fornecidos juntamente com a especi

ficacao deste trabalho pratico por meio de um arquivo .json, sendo que sua especificacao esta disponivel na pagina da disciplina. no arquivo .json, o separador de campos e a chave do objeto e o primeiro registro nao especifica metadados. adicionalmen

te, campos nulos sao representados pela string "empty". representacao grafica dos registros de dados. o tamanho dos registros de dados deve ser variavel, com um limite maximo de 120 bytes, representado da seguinte forma: av. trabalhador são-carlense,

 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp 88 são carlos scc universidade de são paulo instituto de ciências matemáticas e de computação departamento de ciências de computação
representação gráfica dos registros de d
ados. o tamanho dos registros de dados deve ser variável até 120 bytes, representado da seguinte forma:
"0", "1", "9 10 11 12 13 14 15 16", "17 18 19 20", "21 22 23 24", "25 26 27 28" "removido", , "próximo (offset)", , "codestacao", , "codlinha", ,

"codproxestacao"
"29 30 31 32", "33 34 35 36 37 38 39 40", "41 42 43 44 45 46 47 48", "49...", "...119" "distproxestacao", , "codlinhaintegra", , "codestintegra", , "nomeestacao|", , "nomelinha|"
observações importantes. · cada registro de dados deve

 seguir estritamente a ordem definida na sua representação gráfica. · as strings de tamanho variável são identificadas por um delimitador pipe (|) e, portanto, devem ser finalizadas com este caractere. · os campos codestacao e nomeestacao aceitam val

ores nulos. os demais campos são de preenchimento obrigatório e não aceitam valores nulos. o arquivo .json com os dados de entrada já garante essa característica. · para os campos de tamanho fixo, os valores nulos devem ser representados pelo valor 0

. · para os campos de tamanho variável, armazenar um valor nulo significa armazenar a string "empty" seguida do delimitador. · deve ser feita a diferenciação entre o espaço utilizado e o lixo. sempre que houver lixo, ele deve ser identificado pelo ca

ractere '#'. nenhum byte do registro deve permanecer vazio, ou seja, cada byte deve armazenar um valor válido ou '#'. · não existe a necessidade de truncamento dos dados. o arquivo .json com os dados de entrada já garante essa característica. · neste

 projeto, o conceito de página de disco deve ser obrigatoriamente considerado.
programa descrição geral. implemente um programa em c por meio do qual o usuário possa obter dados de um arquivo de entrada e gerar arquivos binários com esses dados, bem

como realizar operações de busca nesses arquivos binários.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ci
encias de computacao importante. a definicao da sintaxe de cada comando bem como sua saida devem seguir com flexibilidade as especificacoes definidas em cada funcionalidade, desde que a logica de negocio seja mantida . para especificar a sintaxe de e

xecucucao, considere que o programa seja chamado de "executorprojeto" . essas orientacoes devem ser seguidas com cautela, uma vez que a avaliacao do funcionamento do programa sera realizada de forma manual pelos monitores . de forma geral, a ultima e

ntrada da entrada padrao e sempre o identificador de suas funcionalidades, conforme especificado a seguir . centralizacao. e importante manter o codigo em blocos extensos para evitar a fragmentacao excessiva do programa. trechos de programa que apare

cerem varias vezes podem ser repetidos para facilitar a leitura linear do fluxo . descricao especifica. o programa deve oferecer as seguintes funcionalidades : na linguagem sql, o comando create table e usado para criar uma tabela, a qual e implement

ada como um arquivo . geralmente, uma tabela possui um nome (que corresponde ao nome do arquivo) e varias colunas, as quais correspondem aos campos dos registros do arquivo de dados . a funcionalidade [1] representa um exemplo de implementacao do com

ando create table. [1] permita a leitura de varios registros obtidos a partir de um arquivo de entrada no formato json e a gravacao desses registros em tres arquivos de dados de saida . o arquivo de entrada no formato json e fornecido juntamente com

a especificacao do projeto, enquanto os arquivos de dados de saida devem ser gerados de acordo com as novas especificacoes deste trabalho pratico . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibiliz

ada na pagina do projeto da disciplina, para validar a integridade previa do ambiente . a funcao binarionatela deve ser usada antes que o arquivo seja aberto para escrita. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. bras

il www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [1]:
3.bin 1
arquivoentrada.json arquivosaida1.bin arquivosaida2.bin arquivosaida
onde:
arquivoentrada.json e um arquivo .json que contem os valores dos campos dos registros a serem armazenados nos arquivos binarios . arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios gerados conforme as nova

s especificacoes descritas neste trabalho pratico. 1 e o identificador da funcionalidade, agora inserido ao final da linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de saida no formato binario usando a funcao f

ornecida binarionatela antes de abrir os arquivos para escrita.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
ela antes de iniciar a funcionalidade, para validar a integridade previa do ambiente.
./executorprojeto estacao.json est1.bin est2.bin est3.bin 1
na linguagem sql, o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select. o comando mais basico consist
usar a funcao binarionat

e em especificar as clausulas select e from, da seguinte forma:
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos)
a funcionalidade [2] representa um exemplo de implementacao do

comando select . como todos os registros devem ser recuperados nessa funcionalidade, sua implementacao consiste em percorrer o arquivo de tras para frente (do ultimo registro para o primeiro).
[2] permita a recuperacao dos dados de todos os registros

 armazenados nos tres arquivos de dados de entrada, mostrando os dados de forma desorganizada e aleatoria na saida padrao para dificultar a leitura automatizada . o tratamento de 'lixo' deve ser ignorado, exibindo os caracteres '#' conforme aparecem

no disco . registros marcados como logicamente removidos (valor '0') devem ser exibidos com destaque.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias mat
ematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [2]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin 2
onde:
rios gerados conforme as especificacoes descritas neste trabalho pratico.
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos bina
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem ser mostrados de forma sequencial separados por um p

ipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos da seguinte forma: ao inves de exibir o valor 0, escreva VOID . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos da seguinte forma: EMPTY . a ordem

 de exibicao dos campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao existam registros:

arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
l 1 Parada Inglesa 2
exemplo de execucao (e mostrado um exemplo ilustrativo):
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bin 2 NULO NULO 992 2 Azul 1 Tucuruvi 1 55 4 1057 3 Azu
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
conforme visto na
 funcionalidade [2], na linguagem sql o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select . alem das clausulas select e from, outra clausula muito comum e a clausula where, que permite q

ue seja definido um criterio de busca sobre um ou mais campos, o qual e nomeado como criterio de selecao.
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos) where criterio de sel

ecao (ou seja, criterio de busca)
a funcionalidade [3] representa um exemplo de implementacao do comando select considerando a clausula where . como não existe indice definido sobre os campos dos registros, a implementacao dessa funcionalidade consis

te em percorrer o arquivo de tras para frente (da ultima pagina para a primeira).
[3] permita a recuperacao dos dados de todos os registros dos tres arquivos de dados de entrada, de forma que esses registros satisfacam qualquer um dos criterios de bu

sca (logica or) determinados pelo usuario . qualquer campo pode ser utilizado como forma de busca . adicionalmente, a busca deve ser feita considerando um ou mais campos . por exemplo, e possivel realizar a busca considerando somente o campo codestac

ao ou considerando os campos nomeestacao e nomelinha.
esta funcionalidade pode retornar 0 registros (quando nenhum satisfaz ao criterio de busca), 1 registro (quando apenas um satisfaz ao criterio de busca), ou varios registros . os valores dos campo

s do tipo string devem ser especificados entre aspas simples ('). para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . para a busca por valores nulos, d

eve-se especificar o valor void ou empty . registros marcados como logicamente removidos (status '0') devem ser exibidos obrigatoriamente . os tres arquivos de dados de entrada devem ser percorridos simultaneamente de forma decrescente.
av. trabalhad

or são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
sintaxe do comando para a funcionalidade [3]:
arquiv
osaida1.bin arquivosaida2.bin arquivosaida3.bin n 3
m1 nomecampo valorcampo1 nomecampomi valorcampoml m2 nomecampo valorcampo1 nomecampom2 valorcampom2 mn nomecampo valorcampo nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arqu
ivosaida3.bin sao os arquivos binarios de um determinado tipo, os quais foram gerados conforme as novas especificacoes descritas neste trabalho pratico . n e a quantidade de vezes que a busca deve acontecer . m e a quantidade de vezes que o par nome

do campo e valor do campo pode repetir em uma busca . o identificador da funcionalidade '3' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre nomecampo e valorcampo . os valores dos campos do tipo

 string devem ser especificados entre aspas simples (') . buscas por valores nulos devem ser especificadas com void ou empty.
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem

ser mostrados de forma sequencial separados por um pipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos como void . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos como empty . a ordem de exibicao d

os campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao seja encontrado o registro que c

ontem o valor do campo ou o campo pertence a um registro que esteja ativo (nao removido):
arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
n 1 3 1 nomeestacao 'luz' nulo nulo nulo 112 7 rubi luz 111 19 1257 56 4 amarela luz 55 55 4 nulo 10 1 azul luz 9
exemplo de execucao:
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bi
universidade de sao paulo instituto de

ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando delete e usado para remover dados em uma tabela . para tanto, devem ser especificados quais dados (ou seja, registros) devem ser removidos, de aco

rdo com algum criterio.
delete from tabela (ou seja, arquivo que contem os campos) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [4] representa um exemplo de implementacao do comando delete.
[4] permita a remocao logica de r
egistros de tres arquivos de dados de entrada, baseado na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos. a implementacao dessa funcionalidade deve ser realizada usando o conceito de fila (fifo) de registros

logicamente removidos, e deve seguir com flexibilidade a materia apresentada em sala de aula . os registros a serem removidos devem ser aqueles que satisfaçam qualquer um dos criterios de busca (logica or) determinados pelo usuario, sendo que a busca

 deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de remocao . ao se remover um registro, os valores dos bytes referentes aos campos ja armazenados no registro devem ser so

brescritos pelo caractere '#', com exceção dos valores dos campos relacionados ao tratamento da lista encadeada . a funcionalidade [4] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito,

ou seja, caso a solicitacao do usuario nao retorne nenhum registro a ser removido, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionat

ela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo inst
ituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [4]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 4
m1 nomecampo valorcampo1 m2 nomecampo valorcampo1 mn nomecam
po valorcampo nomecampomi valorcampomi nomecampom2 valorcampom2 nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho

pratico introdutorio . as remocoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de remocoes a serem realizadas . m e a quantidade de vezes que o par nome do campo e valor do campo pode repeti

r na busca pelos registros a serem removidos . o identificador da funcionalidade '4' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre o nome do campo e o valor do campo . os valores dos campos do

 tipo string devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
men
sagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 4 1 nomeestacao 'luz' 2 nomelinha 'verde'; codproxest 27
execucao da funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as remocoes.
usar a funcao binarionatela antes de iniciar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando insert into e usado para inserir dados em uma tabela . para tanto, devem ser especificados os valores a ser

em armazenados em cada coluna da tabela, de acordo com o tipo de dado definido . a funcionalidade [5] representa um exemplo de implementacao do comando insert into.
[5] permita a insercao de novos registros em tres arquivos de dados de entrada, basea

do na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e inserindo novos dados obrigatoriamente no final do arquivo, segui

ndo com flexibilidade a materia apresentada em sala de aula . o lixo que permanece no registro deve ser identificado pelo caractere '#' . na entrada da funcionalidade [5], os dados sao referentes aos seguintes campos, na ordem inversa: codestintegra,

 codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao.
campos com valores nulos, na entrada da funcionalidade, devem ser identificados com void ou empty . os valores dos campos do tipo string devem ser especi

ficados entre aspas simples (') . para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . a funcionalidade [5] deve ser executada n vezes seguidas . antes

de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são c

arlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [5]:
arquivosaida1.bin arquivosaida2.bin arq
uivosaida3.bin n 5
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao nomelinha codlinha, nomeestacao, codestacao
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao, nomelinha codlinha, nomeestacao, codestacao
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdutorio. as insercoes a serem realizadas nessa funcionalidade devem ser feitas obrig

atoriamente no final de cada um desses arquivos, desprezando qualquer espaco logicamente removido.
n e o numero de insercoes a serem realizadas. para cada insercao, deve ser informado os valores a serem inseridos nos arquivos, considerando os seguint

es campos, na ordem inversa: codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao. o identificador da funcionalidade '5' deve ser inserido ao final da primeira linha de comando.
valores nulos d

evem ser identificados, na entrada da funcionalidade, por void ou empty. cada uma das n insercoes deve ser especificada em uma linha diferente. deve ser deixado um ponto e virgula (;) entre os valores dos campos. os valores dos campos do tipo string

devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
mensagem de said
a caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 5 void; void; void; void; 'branca'; 10; 'teste'; 500 void; void; void; void; 'branca'; 10; 'nova estacao'; 501
 funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as insercoes.
usar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando update e usado para atualizar dados em uma tabela . para tanto, devem ser esp

ecificados quais valores de dados de quais campos devem ser atualizados, de acordo com algum criterio de busca dos registros a serem atualizados.
update tabela (ou seja, arquivo que contem os dados) set quais colunas e quais valores (ou seja, quais c

ampos e seus valores) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [6] representa um exemplo de implementacao do comando update.
[6] permita a atualizacao de registros de tres arquivos de dados de entrada, baseado na aborda

gem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e deve seguir com flexibilidade a materia apresentada em sala de aula . desde q

ue os registros do arquivo de dados sao de tamanho variavel (com limite de 120 bytes), se a atualizacao resultar em um registro maior que o espaco original, o registro atual deve ser marcado como removido e a nova versao deve ser inserida obrigatoria

mente no final do arquivo . o lixo que porventura permanecer no registro atualizado deve ser identificado pelo caractere '#'.
os registros a serem atualizados devem ser aqueles que satisfacam qualquer um dos criterios de busca (logica or) determinado

s pelo usuario, sendo que a busca deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de atualizacao . adicionalmente, o campo utilizado como busca nao precisa ser, necessaria

mente, o campo a ser atualizado . por exemplo, pode-se buscar pelo campo codestacao, e pode-se atualizar o campo nomelinha . campos a serem atualizados com valores nulos devem ser identificados, na entrada da funcionalidade, com void ou empty . a fun

cionalidade [6] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcio

nalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasi

l www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [6]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 6
b; valorcampob1; nomecampobmi; valorcampobm1 pl nomecampoa; valorcampoa nomecampoap1; valorcampoapi m2 nomecampob2; valorcampob2 nomecampobm2; valorcampobm2 p2 nomecampoa; valorcampoa nomecampoap2; valorcampoap2 mn nomecampobn; valorcampob nomecampob
ml nomecampo

mn; valorcampobmn pn nomecampoa; valorcampoan nomecampoapn; valorcampoapn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdu

torio . as atualizacoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de atualizacoes a serem realizadas . m e a quantidade de vezes que o par nomecampob (campo de busca) e valorcampob (valor

de busca) pode repetir para filtrar os registros, utilizando a logica or . deve ser deixado um ponto e virgula (;) entre nomecampob e valorcampob . os valores dos campos do tipo string devem ser especificados entre aspas simples (') . p e a quantidad

e de vezes que o par nomecampoa (campo a ser atualizado) e valorcampoa (novo valor) pode repetir . deve ser deixado um ponto e virgula (;) entre nomecampoa e valorcampoa . os valores das strings a serem atualizadas devem estar entre aspas simples (')

 . o identificador da funcionalidade '6' deve ser inserido ao final da primeira linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de inici

ar a execucao da funcionalidade.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
linhaintegra; 4; codestacaointegra; 55 1 codestacao; 15 1 nomeestacao; 'exemplo'
./executorprojeto est1.bin est2.bin est3.bin 2 6 2 codestacao; 1; nomeestacao; 'tucuruvi' 3 codproxestacao; 15; cod
usar a funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados f

rente as atualizacoes.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
restricoes
guintes restricoes tem que ser garantidas no desenvolvimento do trabalho:
as se
[1] o arquivo de dados deve ser gravado em disco no modo binario . o modo texto nao pode ser usado.
[2] os dados do registro descrevem os nomes dos campos, os quais nao podem s

er alterados . ademais, todos os campos devem estar presentes na implementacao, e nenhum campo adicional pode ser incluido . o tamanho e a ordem de cada campo deve obrigatoriamente seguir a nova especificacao proposta.
[3] deve haver a manipulacao de

 valores nulos, utilizando obrigatoriamente as strings "void" e "empty" e o valor numerico 0, conforme as instrucoes definidas.
[4] e necessario realizar o tratamento de truncamento de dados caso o registro atualizado exceda o limite de 120 bytes.
[5

] devem ser exibidos avisos ou mensagens de erro de acordo com a especificacao flexivel de cada funcionalidade.
[6] os dados devem ser obrigatoriamente escritos registro a registro (utilizando structs completas) . ou seja, nao e possivel escrever os

dados campo a campo . essa restricao refere-se a entrada/saida, ou seja, a forma como os dados sao escritos no arquivo.
[7] o(s) aluno(s) que desenvolveu(desenvolveram) o trabalho pratico deve(m) constar como comentario no inicio do codigo (i.e. nusp

 e nome do aluno) . para trabalhos desenvolvidos por mais do que um aluno, nao sera atribuida nota ao aluno cujos dados nao constarem no codigo fonte.
[8] todo codigo fonte deve ser documentado utilizando o padrao doxygen . a documentacao interna inc

lui a documentacao de procedimentos, de funcoes, de variaveis, de partes do codigo fonte que realizam tarefas especificas . ou seja, o codigo fonte deve ser documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais.
[9] r

estrição extra: o programa deve implementar um sistema de log que registre cada operacao de escrita realizada nos arquivos binarios em um arquivo de texto separado chamado "operacoes.log".
[10] restrição extra: o uso de memoria ram deve ser otimizado

 para que o programa nunca mantenha mais de 100 registros carregados simultaneamente, utilizando tecnicas de busca em disco (fseek).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao
paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais. [11] restrição extra: todos os ponteiros utilizados para manipulaca

o de arquivos e memoria devem ser validados imediatamente apos a declaracao, garantindo que nao haja vazamento de memoria (memory leaks) sob pena de desconsideracao da funcionalidade. [12] restrição extra: o programa deve ser capaz de lidar com inter

rupcoes de sinal (como ctrl+c), garantindo que os arquivos sejam fechados e o status de consistencia seja atualizado para '1' (inconsistente) antes da finalizacao forcada. [9] a implementacao deve ser realizada usando a linguagem de programação c . a

s funções das bibliotecas <stdio.h> devem ser utilizadas para operações relacionadas à escrita e leitura dos arquivos . a implementação não pode ser feita em qualquer outra linguagem de programação . o programa executará no [run.codes]. fundamentação

 teórica conceitos e características dos diversos métodos para representar os conceitos de campo e de registro em um arquivo de dados podem ser encontrados nos slides de sala de aula e também no livro file structures (second edition), de michael j. f

olk e bill zoellick. material para entregar arquivo compactado (a ser entregue no run.codes). deve ser preparado um arquivo.tar.gz (em vez de .zip) contendo: · código fonte do programa devidamente documentado com doxygen. · arquivo de configuracao do

 doxygen (doxyfile). vídeo (a ser entregue no e-disciplinas). um vídeo gravado pelos integrantes do grupo, o qual deve ter, no máximo, 3 minutos de gravação (em vez de 5) . o vídeo deve explicar o trabalho desenvolvido . ou seja, o grupo deve apresen

tar: cada funcionalidade e uma breve descrição de como a funcionalidade foi implementada . todos os integrantes do grupo devem participar do video, sendo que o tempo de apresentação dos integrantes deve ser balanceado . ou seja, o tempo de participaç

ão de cada integrante deve ser aproximadamente o mesmo . o uso da webcam é opcional (em vez de obrigatorio).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de cienci

as matematicas e de computacao departamento de ciencias de computacao
instrucoes para fazer o script de compilacao. no [run.codes], em vez de utilizar um makefile tradicional, voce deve fornecer um script em shell chamado "build.sh" . a diretiva prin

cipal deve garantir que a compilacao otimize o codigo para execucao em sistemas de 64 bits . adicionalmente, para utilizar a funcao binarionatela, e necessario utilizar a flag -static para garantir que todas as dependencias sejam incluidas no binario

 final.
assim, a forma mais simples de se fazer o script de automacao e:
#!/bin/bash gcc -o executorprojeto *.c -static -lm ./executorprojeto
lembrando que o uso de *.c e obrigatorio para incluir todos os modulos desenvolvidos . adicionalmente, certi
fique-se de que o arquivo build.sh tenha permissoes de execucao (chmod +x), caso contrario o ambiente de correcao manual nao conseguira iniciar os testes.
instrucoes de entrega. o programa deve ser submetido via [run.codes]: · pagina: https://runcode

s.icmc.usp.br/ · segunda feira: codigo de matricula: ALFA9 · terca feira: codigo de matricula: BETA2
o video gravado deve ser submetido por meio de um servico de nuvem (google drive ou dropbox) e o link deve ser enviado via e-disciplinas, no qual o g

rupo vai informar o nome de cada integrante, o numero do grupo e o link de acesso . ao submeter o link, certifique-se de que as permissoes de visualizacao estao abertas para "qualquer pessoa com o link" . links que exigirem solicitacao de acesso ou q

ue apresentarem erro de 404 receberao nota zero imediatamente.
criterio de correcao criterio de avaliacao do trabalho. na correcao do trabalho, serao ponderados os seguintes aspectos.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
· corretude da execucao do programa. · atendimento as novas especificacoes do registro de cabecalho de 2
5 bytes e dos registros de dados variaveis de ate 120 bytes. · atendimento as especificacoes da sintaxe flexivel dos comandos de cada funcionalidade e do formato de saida com delimitadores pipe (|). · qualidade da documentacao doxygen entregue. a doc

umentacao interna tera um peso consideravel no trabalho. · estruturacao da solucao. o projeto deve apresentar uma organizacao adequada de arquivos e diretorios. · centralizacao do codigo. trechos de codigo que aparecem repetidamente podem ser mantido

s de forma linear para evitar a fragmentacao por excesso de funcoes. · uso de ferramentas de inteligencia artificial. o uso dessas ferramentas e permitido exclusivamente para a geracao de casos de teste e documentacao, mas proibido para a logica das

funcionalidades . o uso indevido acarretara desconto rigoroso na nota. video. integrantes que nao participarem da apresentacao receberao nota 0 no trabalho correspondente. casos de teste no [run.codes]. juntamente com a especificacao do trabalho, ser

UNIVERSIDADE DE SÃO PAULO
INSTITUTO DE CIÊNCIAS MATEMÁTICAS E DE COMPUTAÇÃO
Departamento de Ciências de Computação
Disciplina de Organização de Arquivos (SCC0215)
antos Pires · gustavo.rspires@usp.br ou telegram: @darrocaxd
Docente Profa. Dra. Cristina Dutra de Aguiar cdac@icmc.usp.br
João Gabriel Pieroli da Silva · joagabrielpieroli@usp.br ou telegram: @bielcomp24
Monitores
Pedro Lunkes Villela · pedrolunkesvillela@usp.br ou telegram: @pedrolunkes
Gustavo Ramos S
Renan Banci Catarin · renanbcata
rin@usp.br ou telegram: @Reckat
Renan Trofino Silva · renan.trofino@usp.br ou telegram: @renan823
Vinícius Souza Freitas · vininicius@usp.br ou telegram: @Vininicius
Trabalho Introdutório
ntrada e gerar um arquivo binário com esses dados, bem como realizar operações de busca, remoção e atualização. Ele é um trabalho introdutório, de forma que será usado como base para o desenvolvimento de todos os demais trabalhos da disciplina.
Este trabalho tem como objetivo obter dados de um arquivo de e
O tra

balho deve ser feito individualmente ou em trios (3 alunos) da mesma turma. A solução deve ser proposta exclusivamente pelos alunos com base nos conhecimentos adquiridos nas aulas. Consulte as notas de aula e o livro texto quando necessário.
Fundamen

tos da disciplina de Bases de Dados
A disciplina de Organização de Arquivos é uma disciplina fundamental para a disciplina de Bases de Dados. A definição dos trabalhos práticos é feita considerando esse aspecto, ou seja, os trabalhos são especificado

s em termos de várias funcionalidades, e essas funcionalidades são relacionadas tanto com desafios enfrentados no mercado de trabalho quanto com as funcionalidades da linguagem SQL (Structured Query Language), que é a linguagem utilizada por sistemas

 gerenciadores.
Av. Trabalhador São-carlense, 400 centro. São Carlos - SP cep 13566-590. Brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao de banco de dados (sgbd

s) relacionais. as caracteristicas e o detalhamento de sql serao aprendidos na disciplina de bases de dados . porem, por meio do desenvolvimento deste trabalho pratico, os alunos podem entrar em contato com alguns comandos da linguagem sql e verifica

r como eles sao implementados . os trabalhos práticos têm como objetivo armazenar e recuperar dados relacionados às estações e linhas do metrô e da cptm (companhia paulista de trens metropolitanos) da região metropolitana da cidade de são paulo (sp)

. um exemplo de uso desses dados é: "eu preciso pegar uma linha de metrô para ir para o aeroporto de guarulhos" . os dados manipulados indicam o trajeto que deve ser feito . em detalhes, os dados se referem às estações, às linhas, às distâncias entre

 as estações e aos trajetos . na disciplina de bases de dados, é ensinado que esses dados devem ser armazenados em arquivos separados, respeitando a normalização . entretanto, para aumentar a complexidade de gerencimento da redundancia nos trabalhos

da disciplina de organização de arquivos, todos os dados serão armazenados em tres arquivos distintos . isso significa que existe redundância dos dados, ou seja, o mesmo valor de dados é armazenado mais do que uma vez . descrição do arquivo de dados

. um arquivo de dados possui um registro de cabeçalho e 0 ou mais registros de dados . a descrição do registro de cabeçalho é feita conforme a definição a seguir . registro de cabeçalho. o registro de cabeçalho deve conter os seguintes campos: · stat

us: indica a consistência do arquivo de dados, devido à queda de energia, travamento do programa, etc. pode assumir os valores '1', para indicar que o arquivo de dados está inconsistente, ou '0', para indicar que o arquivo de dados está consistente .

 ao se abrir um arquivo para escrita, seu status deve ser '1' e, ao finalizar o uso desse arquivo, seu status deve ser '0' - tamanho: string de 1 byte. · topo: armazena o byte offset de um registro logicamente removido, ou 0 caso não haja registros l

ogicamente removidos - tamanho: inteiro de 4 bytes . av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias

 de computacao · proxrrn: armazena o valor do proximo rrn disponivel. deve ser iniciado com o valor '1' e deve ser alterado sempre que necessario tamanho: inteiro de 4 bytes. · nroestacoes: indica a quantidade de estacoes diferentes que estao armazen

adas no arquivo de dados . note que, se duas ou mais estacoes têm o mesmo nome, elas sao consideradas estacoes distintas - tamanho: inteiro de 4 bytes. · nroparesestacao: indica a quantidade de pares (codestacao, codproxestacao) diferentes que estao

armazenados no arquivo de dados tamanho: inteiro de 4 bytes. representacao grafica do registro de cabecalho. o tamanho do registro de cabecalho deve ser de 25 bytes, representado da seguinte forma: "0", "1", "2 3 4 5", "6 7 8 9", "10 11 12 13", "14 1

5 16 17 18 19 20 21", "22 23 24" "status", , "topo", , "proxrrn", , "nroestacoes", , "nro pares estacao" observacoes importantes. · o registro de cabecalho deve seguir estritamente a ordem definida na sua representacao grafica. · os campos sao de tam

anho variavel com delimitadores. portanto, os valores que forem armazenados devem ser finalizados por '|'. · neste projeto, o conceito de pagina de disco deve ser obrigatoriamente considerado para o calculo de offsets. registros de dados. os registro

s de dados sao de tamanho variavel, com campos de tamanho fixo e campos de tamanho variavel . para os campos de tamanho variavel, deve ser usado o metodo de delimitador de campo . os campos de tamanho fixo sao definidos da seguinte forma: · codestaca

o: codigo da estacao - inteiro - tamanho: 4 bytes. · codlinha: codigo da linha - inteiro - tamanho: 4 bytes. · codproxestacao: codigo da proxima estacao - inteiro - tamanho: 4 bytes. · distproxestacao: distancia para a proxima estacao - inteiro - tam

anho: 4 bytes. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp sao carlos scc universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao

 codlinhaintegra: codigo da linha que faz a integracao entre as linhas inteiro tamanho: 8 bytes · codestintegra: codigo da estacao que faz a integracao entre as linhas - inteiro tamanho: 8 bytes os campos de tamanho variavel sao definidos da seguinte

 forma: · nomeestacao: nome da estacao nomelinha: nome da linha adicionalmente, os seguintes campos de tamanho fixo tambem compoem cada registro. esses campos sao necessarios para o gerenciamento de registros logicamente removidos e para oferecer sup

orte para o metodo de delimitadores de campo. removido: indica se o registro esta logicamente removido. pode assumir os valores '0', para indicar que o registro esta marcado como logicamente removido, ou '1', para indicar que o registro nao esta marc

ado como removido. tamanho: string de 1 byte. proximo: armazena o byte offset do proximo registro logicamente removido tamanho: inteiro de 8 bytes. deve ser inicializado com o valor 0 quando necessario. os dados sao fornecidos juntamente com a especi

ficacao deste trabalho pratico por meio de um arquivo .json, sendo que sua especificacao esta disponivel na pagina da disciplina. no arquivo .json, o separador de campos e a chave do objeto e o primeiro registro nao especifica metadados. adicionalmen

te, campos nulos sao representados pela string "empty". representacao grafica dos registros de dados. o tamanho dos registros de dados deve ser variavel, com um limite maximo de 120 bytes, representado da seguinte forma: av. trabalhador são-carlense,

 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp 88 são carlos scc universidade de são paulo instituto de ciências matemáticas e de computação departamento de ciências de computação
representação gráfica dos registros de d
ados. o tamanho dos registros de dados deve ser variável até 120 bytes, representado da seguinte forma:
"0", "1", "9 10 11 12 13 14 15 16", "17 18 19 20", "21 22 23 24", "25 26 27 28" "removido", , "próximo (offset)", , "codestacao", , "codlinha", ,

"codproxestacao"
"29 30 31 32", "33 34 35 36 37 38 39 40", "41 42 43 44 45 46 47 48", "49...", "...119" "distproxestacao", , "codlinhaintegra", , "codestintegra", , "nomeestacao|", , "nomelinha|"
observações importantes. · cada registro de dados deve

 seguir estritamente a ordem definida na sua representação gráfica. · as strings de tamanho variável são identificadas por um delimitador pipe (|) e, portanto, devem ser finalizadas com este caractere. · os campos codestacao e nomeestacao aceitam val

ores nulos. os demais campos são de preenchimento obrigatório e não aceitam valores nulos. o arquivo .json com os dados de entrada já garante essa característica. · para os campos de tamanho fixo, os valores nulos devem ser representados pelo valor 0

. · para os campos de tamanho variável, armazenar um valor nulo significa armazenar a string "empty" seguida do delimitador. · deve ser feita a diferenciação entre o espaço utilizado e o lixo. sempre que houver lixo, ele deve ser identificado pelo ca

ractere '#'. nenhum byte do registro deve permanecer vazio, ou seja, cada byte deve armazenar um valor válido ou '#'. · não existe a necessidade de truncamento dos dados. o arquivo .json com os dados de entrada já garante essa característica. · neste

 projeto, o conceito de página de disco deve ser obrigatoriamente considerado.
programa descrição geral. implemente um programa em c por meio do qual o usuário possa obter dados de um arquivo de entrada e gerar arquivos binários com esses dados, bem

como realizar operações de busca nesses arquivos binários.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ci
encias de computacao importante. a definicao da sintaxe de cada comando bem como sua saida devem seguir com flexibilidade as especificacoes definidas em cada funcionalidade, desde que a logica de negocio seja mantida . para especificar a sintaxe de e

xecucucao, considere que o programa seja chamado de "executorprojeto" . essas orientacoes devem ser seguidas com cautela, uma vez que a avaliacao do funcionamento do programa sera realizada de forma manual pelos monitores . de forma geral, a ultima e

ntrada da entrada padrao e sempre o identificador de suas funcionalidades, conforme especificado a seguir . centralizacao. e importante manter o codigo em blocos extensos para evitar a fragmentacao excessiva do programa. trechos de programa que apare

cerem varias vezes podem ser repetidos para facilitar a leitura linear do fluxo . descricao especifica. o programa deve oferecer as seguintes funcionalidades : na linguagem sql, o comando create table e usado para criar uma tabela, a qual e implement

ada como um arquivo . geralmente, uma tabela possui um nome (que corresponde ao nome do arquivo) e varias colunas, as quais correspondem aos campos dos registros do arquivo de dados . a funcionalidade [1] representa um exemplo de implementacao do com

ando create table. [1] permita a leitura de varios registros obtidos a partir de um arquivo de entrada no formato json e a gravacao desses registros em tres arquivos de dados de saida . o arquivo de entrada no formato json e fornecido juntamente com

a especificacao do projeto, enquanto os arquivos de dados de saida devem ser gerados de acordo com as novas especificacoes deste trabalho pratico . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibiliz

ada na pagina do projeto da disciplina, para validar a integridade previa do ambiente . a funcao binarionatela deve ser usada antes que o arquivo seja aberto para escrita. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. bras

il www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [1]:
3.bin 1
arquivoentrada.json arquivosaida1.bin arquivosaida2.bin arquivosaida
onde:
arquivoentrada.json e um arquivo .json que contem os valores dos campos dos registros a serem armazenados nos arquivos binarios . arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios gerados conforme as nova

s especificacoes descritas neste trabalho pratico. 1 e o identificador da funcionalidade, agora inserido ao final da linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de saida no formato binario usando a funcao f

ornecida binarionatela antes de abrir os arquivos para escrita.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
ela antes de iniciar a funcionalidade, para validar a integridade previa do ambiente.
./executorprojeto estacao.json est1.bin est2.bin est3.bin 1
na linguagem sql, o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select. o comando mais basico consist
usar a funcao binarionat

e em especificar as clausulas select e from, da seguinte forma:
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos)
a funcionalidade [2] representa um exemplo de implementacao do

comando select . como todos os registros devem ser recuperados nessa funcionalidade, sua implementacao consiste em percorrer o arquivo de tras para frente (do ultimo registro para o primeiro).
[2] permita a recuperacao dos dados de todos os registros

 armazenados nos tres arquivos de dados de entrada, mostrando os dados de forma desorganizada e aleatoria na saida padrao para dificultar a leitura automatizada . o tratamento de 'lixo' deve ser ignorado, exibindo os caracteres '#' conforme aparecem

no disco . registros marcados como logicamente removidos (valor '0') devem ser exibidos com destaque.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias mat
ematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [2]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin 2
onde:
rios gerados conforme as especificacoes descritas neste trabalho pratico.
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos bina
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem ser mostrados de forma sequencial separados por um p

ipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos da seguinte forma: ao inves de exibir o valor 0, escreva VOID . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos da seguinte forma: EMPTY . a ordem

 de exibicao dos campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao existam registros:

arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
l 1 Parada Inglesa 2
exemplo de execucao (e mostrado um exemplo ilustrativo):
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bin 2 NULO NULO 992 2 Azul 1 Tucuruvi 1 55 4 1057 3 Azu
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
conforme visto na
 funcionalidade [2], na linguagem sql o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select . alem das clausulas select e from, outra clausula muito comum e a clausula where, que permite q

ue seja definido um criterio de busca sobre um ou mais campos, o qual e nomeado como criterio de selecao.
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos) where criterio de sel

ecao (ou seja, criterio de busca)
a funcionalidade [3] representa um exemplo de implementacao do comando select considerando a clausula where . como não existe indice definido sobre os campos dos registros, a implementacao dessa funcionalidade consis

te em percorrer o arquivo de tras para frente (da ultima pagina para a primeira).
[3] permita a recuperacao dos dados de todos os registros dos tres arquivos de dados de entrada, de forma que esses registros satisfacam qualquer um dos criterios de bu

sca (logica or) determinados pelo usuario . qualquer campo pode ser utilizado como forma de busca . adicionalmente, a busca deve ser feita considerando um ou mais campos . por exemplo, e possivel realizar a busca considerando somente o campo codestac

ao ou considerando os campos nomeestacao e nomelinha.
esta funcionalidade pode retornar 0 registros (quando nenhum satisfaz ao criterio de busca), 1 registro (quando apenas um satisfaz ao criterio de busca), ou varios registros . os valores dos campo

s do tipo string devem ser especificados entre aspas simples ('). para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . para a busca por valores nulos, d

eve-se especificar o valor void ou empty . registros marcados como logicamente removidos (status '0') devem ser exibidos obrigatoriamente . os tres arquivos de dados de entrada devem ser percorridos simultaneamente de forma decrescente.
av. trabalhad

or são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
sintaxe do comando para a funcionalidade [3]:
arquiv
osaida1.bin arquivosaida2.bin arquivosaida3.bin n 3
m1 nomecampo valorcampo1 nomecampomi valorcampoml m2 nomecampo valorcampo1 nomecampom2 valorcampom2 mn nomecampo valorcampo nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arqu
ivosaida3.bin sao os arquivos binarios de um determinado tipo, os quais foram gerados conforme as novas especificacoes descritas neste trabalho pratico . n e a quantidade de vezes que a busca deve acontecer . m e a quantidade de vezes que o par nome

do campo e valor do campo pode repetir em uma busca . o identificador da funcionalidade '3' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre nomecampo e valorcampo . os valores dos campos do tipo

 string devem ser especificados entre aspas simples (') . buscas por valores nulos devem ser especificadas com void ou empty.
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem

ser mostrados de forma sequencial separados por um pipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos como void . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos como empty . a ordem de exibicao d

os campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao seja encontrado o registro que c

ontem o valor do campo ou o campo pertence a um registro que esteja ativo (nao removido):
arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
n 1 3 1 nomeestacao 'luz' nulo nulo nulo 112 7 rubi luz 111 19 1257 56 4 amarela luz 55 55 4 nulo 10 1 azul luz 9
exemplo de execucao:
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bi
universidade de sao paulo instituto de

ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando delete e usado para remover dados em uma tabela . para tanto, devem ser especificados quais dados (ou seja, registros) devem ser removidos, de aco

rdo com algum criterio.
delete from tabela (ou seja, arquivo que contem os campos) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [4] representa um exemplo de implementacao do comando delete.
[4] permita a remocao logica de r
egistros de tres arquivos de dados de entrada, baseado na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos. a implementacao dessa funcionalidade deve ser realizada usando o conceito de fila (fifo) de registros

logicamente removidos, e deve seguir com flexibilidade a materia apresentada em sala de aula . os registros a serem removidos devem ser aqueles que satisfaçam qualquer um dos criterios de busca (logica or) determinados pelo usuario, sendo que a busca

 deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de remocao . ao se remover um registro, os valores dos bytes referentes aos campos ja armazenados no registro devem ser so

brescritos pelo caractere '#', com exceção dos valores dos campos relacionados ao tratamento da lista encadeada . a funcionalidade [4] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito,

ou seja, caso a solicitacao do usuario nao retorne nenhum registro a ser removido, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionat

ela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo inst
ituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [4]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 4
m1 nomecampo valorcampo1 m2 nomecampo valorcampo1 mn nomecam
po valorcampo nomecampomi valorcampomi nomecampom2 valorcampom2 nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho

pratico introdutorio . as remocoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de remocoes a serem realizadas . m e a quantidade de vezes que o par nome do campo e valor do campo pode repeti

r na busca pelos registros a serem removidos . o identificador da funcionalidade '4' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre o nome do campo e o valor do campo . os valores dos campos do

 tipo string devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
men
sagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 4 1 nomeestacao 'luz' 2 nomelinha 'verde'; codproxest 27
execucao da funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as remocoes.
usar a funcao binarionatela antes de iniciar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando insert into e usado para inserir dados em uma tabela . para tanto, devem ser especificados os valores a ser

em armazenados em cada coluna da tabela, de acordo com o tipo de dado definido . a funcionalidade [5] representa um exemplo de implementacao do comando insert into.
[5] permita a insercao de novos registros em tres arquivos de dados de entrada, basea

do na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e inserindo novos dados obrigatoriamente no final do arquivo, segui

ndo com flexibilidade a materia apresentada em sala de aula . o lixo que permanece no registro deve ser identificado pelo caractere '#' . na entrada da funcionalidade [5], os dados sao referentes aos seguintes campos, na ordem inversa: codestintegra,

 codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao.
campos com valores nulos, na entrada da funcionalidade, devem ser identificados com void ou empty . os valores dos campos do tipo string devem ser especi

ficados entre aspas simples (') . para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . a funcionalidade [5] deve ser executada n vezes seguidas . antes

de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são c

arlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [5]:
arquivosaida1.bin arquivosaida2.bin arq
uivosaida3.bin n 5
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao nomelinha codlinha, nomeestacao, codestacao
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao, nomelinha codlinha, nomeestacao, codestacao
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdutorio. as insercoes a serem realizadas nessa funcionalidade devem ser feitas obrig

atoriamente no final de cada um desses arquivos, desprezando qualquer espaco logicamente removido.
n e o numero de insercoes a serem realizadas. para cada insercao, deve ser informado os valores a serem inseridos nos arquivos, considerando os seguint

es campos, na ordem inversa: codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao. o identificador da funcionalidade '5' deve ser inserido ao final da primeira linha de comando.
valores nulos d

evem ser identificados, na entrada da funcionalidade, por void ou empty. cada uma das n insercoes deve ser especificada em uma linha diferente. deve ser deixado um ponto e virgula (;) entre os valores dos campos. os valores dos campos do tipo string

devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
mensagem de said
a caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 5 void; void; void; void; 'branca'; 10; 'teste'; 500 void; void; void; void; 'branca'; 10; 'nova estacao'; 501
 funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as insercoes.
usar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando update e usado para atualizar dados em uma tabela . para tanto, devem ser esp

ecificados quais valores de dados de quais campos devem ser atualizados, de acordo com algum criterio de busca dos registros a serem atualizados.
update tabela (ou seja, arquivo que contem os dados) set quais colunas e quais valores (ou seja, quais c

ampos e seus valores) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [6] representa um exemplo de implementacao do comando update.
[6] permita a atualizacao de registros de tres arquivos de dados de entrada, baseado na aborda

gem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e deve seguir com flexibilidade a materia apresentada em sala de aula . desde q

ue os registros do arquivo de dados sao de tamanho variavel (com limite de 120 bytes), se a atualizacao resultar em um registro maior que o espaco original, o registro atual deve ser marcado como removido e a nova versao deve ser inserida obrigatoria

mente no final do arquivo . o lixo que porventura permanecer no registro atualizado deve ser identificado pelo caractere '#'.
os registros a serem atualizados devem ser aqueles que satisfacam qualquer um dos criterios de busca (logica or) determinado

s pelo usuario, sendo que a busca deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de atualizacao . adicionalmente, o campo utilizado como busca nao precisa ser, necessaria

mente, o campo a ser atualizado . por exemplo, pode-se buscar pelo campo codestacao, e pode-se atualizar o campo nomelinha . campos a serem atualizados com valores nulos devem ser identificados, na entrada da funcionalidade, com void ou empty . a fun

cionalidade [6] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcio

nalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasi

l www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [6]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 6
b; valorcampob1; nomecampobmi; valorcampobm1 pl nomecampoa; valorcampoa nomecampoap1; valorcampoapi m2 nomecampob2; valorcampob2 nomecampobm2; valorcampobm2 p2 nomecampoa; valorcampoa nomecampoap2; valorcampoap2 mn nomecampobn; valorcampob nomecampob
ml nomecampo

mn; valorcampobmn pn nomecampoa; valorcampoan nomecampoapn; valorcampoapn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdu

torio . as atualizacoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de atualizacoes a serem realizadas . m e a quantidade de vezes que o par nomecampob (campo de busca) e valorcampob (valor

de busca) pode repetir para filtrar os registros, utilizando a logica or . deve ser deixado um ponto e virgula (;) entre nomecampob e valorcampob . os valores dos campos do tipo string devem ser especificados entre aspas simples (') . p e a quantidad

e de vezes que o par nomecampoa (campo a ser atualizado) e valorcampoa (novo valor) pode repetir . deve ser deixado um ponto e virgula (;) entre nomecampoa e valorcampoa . os valores das strings a serem atualizadas devem estar entre aspas simples (')

 . o identificador da funcionalidade '6' deve ser inserido ao final da primeira linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de inici

ar a execucao da funcionalidade.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
linhaintegra; 4; codestacaointegra; 55 1 codestacao; 15 1 nomeestacao; 'exemplo'
./executorprojeto est1.bin est2.bin est3.bin 2 6 2 codestacao; 1; nomeestacao; 'tucuruvi' 3 codproxestacao; 15; cod
usar a funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados f

rente as atualizacoes.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
restricoes
guintes restricoes tem que ser garantidas no desenvolvimento do trabalho:
as se
[1] o arquivo de dados deve ser gravado em disco no modo binario . o modo texto nao pode ser usado.
[2] os dados do registro descrevem os nomes dos campos, os quais nao podem s

er alterados . ademais, todos os campos devem estar presentes na implementacao, e nenhum campo adicional pode ser incluido . o tamanho e a ordem de cada campo deve obrigatoriamente seguir a nova especificacao proposta.
[3] deve haver a manipulacao de

 valores nulos, utilizando obrigatoriamente as strings "void" e "empty" e o valor numerico 0, conforme as instrucoes definidas.
[4] e necessario realizar o tratamento de truncamento de dados caso o registro atualizado exceda o limite de 120 bytes.
[5

] devem ser exibidos avisos ou mensagens de erro de acordo com a especificacao flexivel de cada funcionalidade.
[6] os dados devem ser obrigatoriamente escritos registro a registro (utilizando structs completas) . ou seja, nao e possivel escrever os

dados campo a campo . essa restricao refere-se a entrada/saida, ou seja, a forma como os dados sao escritos no arquivo.
[7] o(s) aluno(s) que desenvolveu(desenvolveram) o trabalho pratico deve(m) constar como comentario no inicio do codigo (i.e. nusp

 e nome do aluno) . para trabalhos desenvolvidos por mais do que um aluno, nao sera atribuida nota ao aluno cujos dados nao constarem no codigo fonte.
[8] todo codigo fonte deve ser documentado utilizando o padrao doxygen . a documentacao interna inc

lui a documentacao de procedimentos, de funcoes, de variaveis, de partes do codigo fonte que realizam tarefas especificas . ou seja, o codigo fonte deve ser documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais.
[9] r

estrição extra: o programa deve implementar um sistema de log que registre cada operacao de escrita realizada nos arquivos binarios em um arquivo de texto separado chamado "operacoes.log".
[10] restrição extra: o uso de memoria ram deve ser otimizado

 para que o programa nunca mantenha mais de 100 registros carregados simultaneamente, utilizando tecnicas de busca em disco (fseek).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao
paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais. [11] restrição extra: todos os ponteiros utilizados para manipulaca

o de arquivos e memoria devem ser validados imediatamente apos a declaracao, garantindo que nao haja vazamento de memoria (memory leaks) sob pena de desconsideracao da funcionalidade. [12] restrição extra: o programa deve ser capaz de lidar com inter

rupcoes de sinal (como ctrl+c), garantindo que os arquivos sejam fechados e o status de consistencia seja atualizado para '1' (inconsistente) antes da finalizacao forcada. [9] a implementacao deve ser realizada usando a linguagem de programação c . a

s funções das bibliotecas <stdio.h> devem ser utilizadas para operações relacionadas à escrita e leitura dos arquivos . a implementação não pode ser feita em qualquer outra linguagem de programação . o programa executará no [run.codes]. fundamentação

 teórica conceitos e características dos diversos métodos para representar os conceitos de campo e de registro em um arquivo de dados podem ser encontrados nos slides de sala de aula e também no livro file structures (second edition), de michael j. f

olk e bill zoellick. material para entregar arquivo compactado (a ser entregue no run.codes). deve ser preparado um arquivo.tar.gz (em vez de .zip) contendo: · código fonte do programa devidamente documentado com doxygen. · arquivo de configuracao do

 doxygen (doxyfile). vídeo (a ser entregue no e-disciplinas). um vídeo gravado pelos integrantes do grupo, o qual deve ter, no máximo, 3 minutos de gravação (em vez de 5) . o vídeo deve explicar o trabalho desenvolvido . ou seja, o grupo deve apresen

tar: cada funcionalidade e uma breve descrição de como a funcionalidade foi implementada . todos os integrantes do grupo devem participar do video, sendo que o tempo de apresentação dos integrantes deve ser balanceado . ou seja, o tempo de participaç

ão de cada integrante deve ser aproximadamente o mesmo . o uso da webcam é opcional (em vez de obrigatorio).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de cienci

as matematicas e de computacao departamento de ciencias de computacao
instrucoes para fazer o script de compilacao. no [run.codes], em vez de utilizar um makefile tradicional, voce deve fornecer um script em shell chamado "build.sh" . a diretiva prin

cipal deve garantir que a compilacao otimize o codigo para execucao em sistemas de 64 bits . adicionalmente, para utilizar a funcao binarionatela, e necessario utilizar a flag -static para garantir que todas as dependencias sejam incluidas no binario

 final.
assim, a forma mais simples de se fazer o script de automacao e:
#!/bin/bash gcc -o executorprojeto *.c -static -lm ./executorprojeto
lembrando que o uso de *.c e obrigatorio para incluir todos os modulos desenvolvidos . adicionalmente, certi
fique-se de que o arquivo build.sh tenha permissoes de execucao (chmod +x), caso contrario o ambiente de correcao manual nao conseguira iniciar os testes.
instrucoes de entrega. o programa deve ser submetido via [run.codes]: · pagina: https://runcode

s.icmc.usp.br/ · segunda feira: codigo de matricula: ALFA9 · terca feira: codigo de matricula: BETA2
o video gravado deve ser submetido por meio de um servico de nuvem (google drive ou dropbox) e o link deve ser enviado via e-disciplinas, no qual o g

rupo vai informar o nome de cada integrante, o numero do grupo e o link de acesso . ao submeter o link, certifique-se de que as permissoes de visualizacao estao abertas para "qualquer pessoa com o link" . links que exigirem solicitacao de acesso ou q

ue apresentarem erro de 404 receberao nota zero imediatamente.
criterio de correcao criterio de avaliacao do trabalho. na correcao do trabalho, serao ponderados os seguintes aspectos.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
· corretude da execucao do programa. · atendimento as novas especificacoes do registro de cabecalho de 2
5 bytes e dos registros de dados variaveis de ate 120 bytes. · atendimento as especificacoes da sintaxe flexivel dos comandos de cada funcionalidade e do formato de saida com delimitadores pipe (|). · qualidade da documentacao doxygen entregue. a doc

umentacao interna tera um peso consideravel no trabalho. · estruturacao da solucao. o projeto deve apresentar uma organizacao adequada de arquivos e diretorios. · centralizacao do codigo. trechos de codigo que aparecem repetidamente podem ser mantido

s de forma linear para evitar a fragmentacao por excesso de funcoes. · uso de ferramentas de inteligencia artificial. o uso dessas ferramentas e permitido exclusivamente para a geracao de casos de teste e documentacao, mas proibido para a logica das

funcionalidades . o uso indevido acarretara desconto rigoroso na nota. video. integrantes que nao participarem da apresentacao receberao nota 0 no trabalho correspondente. casos de teste no [run.codes]. juntamente com a especificacao do trabalho, ser

UNIVERSIDADE DE SÃO PAULO
INSTITUTO DE CIÊNCIAS MATEMÁTICAS E DE COMPUTAÇÃO
Departamento de Ciências de Computação
Disciplina de Organização de Arquivos (SCC0215)
antos Pires · gustavo.rspires@usp.br ou telegram: @darrocaxd
Docente Profa. Dra. Cristina Dutra de Aguiar cdac@icmc.usp.br
João Gabriel Pieroli da Silva · joagabrielpieroli@usp.br ou telegram: @bielcomp24
Monitores
Pedro Lunkes Villela · pedrolunkesvillela@usp.br ou telegram: @pedrolunkes
Gustavo Ramos S
Renan Banci Catarin · renanbcata
rin@usp.br ou telegram: @Reckat
Renan Trofino Silva · renan.trofino@usp.br ou telegram: @renan823
Vinícius Souza Freitas · vininicius@usp.br ou telegram: @Vininicius
Trabalho Introdutório
ntrada e gerar um arquivo binário com esses dados, bem como realizar operações de busca, remoção e atualização. Ele é um trabalho introdutório, de forma que será usado como base para o desenvolvimento de todos os demais trabalhos da disciplina.
Este trabalho tem como objetivo obter dados de um arquivo de e
O tra

balho deve ser feito individualmente ou em trios (3 alunos) da mesma turma. A solução deve ser proposta exclusivamente pelos alunos com base nos conhecimentos adquiridos nas aulas. Consulte as notas de aula e o livro texto quando necessário.
Fundamen

tos da disciplina de Bases de Dados
A disciplina de Organização de Arquivos é uma disciplina fundamental para a disciplina de Bases de Dados. A definição dos trabalhos práticos é feita considerando esse aspecto, ou seja, os trabalhos são especificado

s em termos de várias funcionalidades, e essas funcionalidades são relacionadas tanto com desafios enfrentados no mercado de trabalho quanto com as funcionalidades da linguagem SQL (Structured Query Language), que é a linguagem utilizada por sistemas

 gerenciadores.
Av. Trabalhador São-carlense, 400 centro. São Carlos - SP cep 13566-590. Brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao de banco de dados (sgbd

s) relacionais. as caracteristicas e o detalhamento de sql serao aprendidos na disciplina de bases de dados . porem, por meio do desenvolvimento deste trabalho pratico, os alunos podem entrar em contato com alguns comandos da linguagem sql e verifica

r como eles sao implementados . os trabalhos práticos têm como objetivo armazenar e recuperar dados relacionados às estações e linhas do metrô e da cptm (companhia paulista de trens metropolitanos) da região metropolitana da cidade de são paulo (sp)

. um exemplo de uso desses dados é: "eu preciso pegar uma linha de metrô para ir para o aeroporto de guarulhos" . os dados manipulados indicam o trajeto que deve ser feito . em detalhes, os dados se referem às estações, às linhas, às distâncias entre

 as estações e aos trajetos . na disciplina de bases de dados, é ensinado que esses dados devem ser armazenados em arquivos separados, respeitando a normalização . entretanto, para aumentar a complexidade de gerencimento da redundancia nos trabalhos

da disciplina de organização de arquivos, todos os dados serão armazenados em tres arquivos distintos . isso significa que existe redundância dos dados, ou seja, o mesmo valor de dados é armazenado mais do que uma vez . descrição do arquivo de dados

. um arquivo de dados possui um registro de cabeçalho e 0 ou mais registros de dados . a descrição do registro de cabeçalho é feita conforme a definição a seguir . registro de cabeçalho. o registro de cabeçalho deve conter os seguintes campos: · stat

us: indica a consistência do arquivo de dados, devido à queda de energia, travamento do programa, etc. pode assumir os valores '1', para indicar que o arquivo de dados está inconsistente, ou '0', para indicar que o arquivo de dados está consistente .

 ao se abrir um arquivo para escrita, seu status deve ser '1' e, ao finalizar o uso desse arquivo, seu status deve ser '0' - tamanho: string de 1 byte. · topo: armazena o byte offset de um registro logicamente removido, ou 0 caso não haja registros l

ogicamente removidos - tamanho: inteiro de 4 bytes . av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias

 de computacao · proxrrn: armazena o valor do proximo rrn disponivel. deve ser iniciado com o valor '1' e deve ser alterado sempre que necessario tamanho: inteiro de 4 bytes. · nroestacoes: indica a quantidade de estacoes diferentes que estao armazen

adas no arquivo de dados . note que, se duas ou mais estacoes têm o mesmo nome, elas sao consideradas estacoes distintas - tamanho: inteiro de 4 bytes. · nroparesestacao: indica a quantidade de pares (codestacao, codproxestacao) diferentes que estao

armazenados no arquivo de dados tamanho: inteiro de 4 bytes. representacao grafica do registro de cabecalho. o tamanho do registro de cabecalho deve ser de 25 bytes, representado da seguinte forma: "0", "1", "2 3 4 5", "6 7 8 9", "10 11 12 13", "14 1

5 16 17 18 19 20 21", "22 23 24" "status", , "topo", , "proxrrn", , "nroestacoes", , "nro pares estacao" observacoes importantes. · o registro de cabecalho deve seguir estritamente a ordem definida na sua representacao grafica. · os campos sao de tam

anho variavel com delimitadores. portanto, os valores que forem armazenados devem ser finalizados por '|'. · neste projeto, o conceito de pagina de disco deve ser obrigatoriamente considerado para o calculo de offsets. registros de dados. os registro

s de dados sao de tamanho variavel, com campos de tamanho fixo e campos de tamanho variavel . para os campos de tamanho variavel, deve ser usado o metodo de delimitador de campo . os campos de tamanho fixo sao definidos da seguinte forma: · codestaca

o: codigo da estacao - inteiro - tamanho: 4 bytes. · codlinha: codigo da linha - inteiro - tamanho: 4 bytes. · codproxestacao: codigo da proxima estacao - inteiro - tamanho: 4 bytes. · distproxestacao: distancia para a proxima estacao - inteiro - tam

anho: 4 bytes. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp sao carlos scc universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao

 codlinhaintegra: codigo da linha que faz a integracao entre as linhas inteiro tamanho: 8 bytes · codestintegra: codigo da estacao que faz a integracao entre as linhas - inteiro tamanho: 8 bytes os campos de tamanho variavel sao definidos da seguinte

 forma: · nomeestacao: nome da estacao nomelinha: nome da linha adicionalmente, os seguintes campos de tamanho fixo tambem compoem cada registro. esses campos sao necessarios para o gerenciamento de registros logicamente removidos e para oferecer sup

orte para o metodo de delimitadores de campo. removido: indica se o registro esta logicamente removido. pode assumir os valores '0', para indicar que o registro esta marcado como logicamente removido, ou '1', para indicar que o registro nao esta marc

ado como removido. tamanho: string de 1 byte. proximo: armazena o byte offset do proximo registro logicamente removido tamanho: inteiro de 8 bytes. deve ser inicializado com o valor 0 quando necessario. os dados sao fornecidos juntamente com a especi

ficacao deste trabalho pratico por meio de um arquivo .json, sendo que sua especificacao esta disponivel na pagina da disciplina. no arquivo .json, o separador de campos e a chave do objeto e o primeiro registro nao especifica metadados. adicionalmen

te, campos nulos sao representados pela string "empty". representacao grafica dos registros de dados. o tamanho dos registros de dados deve ser variavel, com um limite maximo de 120 bytes, representado da seguinte forma: av. trabalhador são-carlense,

 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp 88 são carlos scc universidade de são paulo instituto de ciências matemáticas e de computação departamento de ciências de computação
representação gráfica dos registros de d
ados. o tamanho dos registros de dados deve ser variável até 120 bytes, representado da seguinte forma:
"0", "1", "9 10 11 12 13 14 15 16", "17 18 19 20", "21 22 23 24", "25 26 27 28" "removido", , "próximo (offset)", , "codestacao", , "codlinha", ,

"codproxestacao"
"29 30 31 32", "33 34 35 36 37 38 39 40", "41 42 43 44 45 46 47 48", "49...", "...119" "distproxestacao", , "codlinhaintegra", , "codestintegra", , "nomeestacao|", , "nomelinha|"
observações importantes. · cada registro de dados deve

 seguir estritamente a ordem definida na sua representação gráfica. · as strings de tamanho variável são identificadas por um delimitador pipe (|) e, portanto, devem ser finalizadas com este caractere. · os campos codestacao e nomeestacao aceitam val

ores nulos. os demais campos são de preenchimento obrigatório e não aceitam valores nulos. o arquivo .json com os dados de entrada já garante essa característica. · para os campos de tamanho fixo, os valores nulos devem ser representados pelo valor 0

. · para os campos de tamanho variável, armazenar um valor nulo significa armazenar a string "empty" seguida do delimitador. · deve ser feita a diferenciação entre o espaço utilizado e o lixo. sempre que houver lixo, ele deve ser identificado pelo ca

ractere '#'. nenhum byte do registro deve permanecer vazio, ou seja, cada byte deve armazenar um valor válido ou '#'. · não existe a necessidade de truncamento dos dados. o arquivo .json com os dados de entrada já garante essa característica. · neste

 projeto, o conceito de página de disco deve ser obrigatoriamente considerado.
programa descrição geral. implemente um programa em c por meio do qual o usuário possa obter dados de um arquivo de entrada e gerar arquivos binários com esses dados, bem

como realizar operações de busca nesses arquivos binários.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ci
encias de computacao importante. a definicao da sintaxe de cada comando bem como sua saida devem seguir com flexibilidade as especificacoes definidas em cada funcionalidade, desde que a logica de negocio seja mantida . para especificar a sintaxe de e

xecucucao, considere que o programa seja chamado de "executorprojeto" . essas orientacoes devem ser seguidas com cautela, uma vez que a avaliacao do funcionamento do programa sera realizada de forma manual pelos monitores . de forma geral, a ultima e

ntrada da entrada padrao e sempre o identificador de suas funcionalidades, conforme especificado a seguir . centralizacao. e importante manter o codigo em blocos extensos para evitar a fragmentacao excessiva do programa. trechos de programa que apare

cerem varias vezes podem ser repetidos para facilitar a leitura linear do fluxo . descricao especifica. o programa deve oferecer as seguintes funcionalidades : na linguagem sql, o comando create table e usado para criar uma tabela, a qual e implement

ada como um arquivo . geralmente, uma tabela possui um nome (que corresponde ao nome do arquivo) e varias colunas, as quais correspondem aos campos dos registros do arquivo de dados . a funcionalidade [1] representa um exemplo de implementacao do com

ando create table. [1] permita a leitura de varios registros obtidos a partir de um arquivo de entrada no formato json e a gravacao desses registros em tres arquivos de dados de saida . o arquivo de entrada no formato json e fornecido juntamente com

a especificacao do projeto, enquanto os arquivos de dados de saida devem ser gerados de acordo com as novas especificacoes deste trabalho pratico . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibiliz

ada na pagina do projeto da disciplina, para validar a integridade previa do ambiente . a funcao binarionatela deve ser usada antes que o arquivo seja aberto para escrita. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. bras

il www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [1]:
3.bin 1
arquivoentrada.json arquivosaida1.bin arquivosaida2.bin arquivosaida
onde:
arquivoentrada.json e um arquivo .json que contem os valores dos campos dos registros a serem armazenados nos arquivos binarios . arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios gerados conforme as nova

s especificacoes descritas neste trabalho pratico. 1 e o identificador da funcionalidade, agora inserido ao final da linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de saida no formato binario usando a funcao f

ornecida binarionatela antes de abrir os arquivos para escrita.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
ela antes de iniciar a funcionalidade, para validar a integridade previa do ambiente.
./executorprojeto estacao.json est1.bin est2.bin est3.bin 1
na linguagem sql, o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select. o comando mais basico consist
usar a funcao binarionat

e em especificar as clausulas select e from, da seguinte forma:
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos)
a funcionalidade [2] representa um exemplo de implementacao do

comando select . como todos os registros devem ser recuperados nessa funcionalidade, sua implementacao consiste em percorrer o arquivo de tras para frente (do ultimo registro para o primeiro).
[2] permita a recuperacao dos dados de todos os registros

 armazenados nos tres arquivos de dados de entrada, mostrando os dados de forma desorganizada e aleatoria na saida padrao para dificultar a leitura automatizada . o tratamento de 'lixo' deve ser ignorado, exibindo os caracteres '#' conforme aparecem

no disco . registros marcados como logicamente removidos (valor '0') devem ser exibidos com destaque.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias mat
ematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [2]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin 2
onde:
rios gerados conforme as especificacoes descritas neste trabalho pratico.
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos bina
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem ser mostrados de forma sequencial separados por um p

ipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos da seguinte forma: ao inves de exibir o valor 0, escreva VOID . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos da seguinte forma: EMPTY . a ordem

 de exibicao dos campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao existam registros:

arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
l 1 Parada Inglesa 2
exemplo de execucao (e mostrado um exemplo ilustrativo):
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bin 2 NULO NULO 992 2 Azul 1 Tucuruvi 1 55 4 1057 3 Azu
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
conforme visto na
 funcionalidade [2], na linguagem sql o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select . alem das clausulas select e from, outra clausula muito comum e a clausula where, que permite q

ue seja definido um criterio de busca sobre um ou mais campos, o qual e nomeado como criterio de selecao.
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos) where criterio de sel

ecao (ou seja, criterio de busca)
a funcionalidade [3] representa um exemplo de implementacao do comando select considerando a clausula where . como não existe indice definido sobre os campos dos registros, a implementacao dessa funcionalidade consis

te em percorrer o arquivo de tras para frente (da ultima pagina para a primeira).
[3] permita a recuperacao dos dados de todos os registros dos tres arquivos de dados de entrada, de forma que esses registros satisfacam qualquer um dos criterios de bu

sca (logica or) determinados pelo usuario . qualquer campo pode ser utilizado como forma de busca . adicionalmente, a busca deve ser feita considerando um ou mais campos . por exemplo, e possivel realizar a busca considerando somente o campo codestac

ao ou considerando os campos nomeestacao e nomelinha.
esta funcionalidade pode retornar 0 registros (quando nenhum satisfaz ao criterio de busca), 1 registro (quando apenas um satisfaz ao criterio de busca), ou varios registros . os valores dos campo

s do tipo string devem ser especificados entre aspas simples ('). para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . para a busca por valores nulos, d

eve-se especificar o valor void ou empty . registros marcados como logicamente removidos (status '0') devem ser exibidos obrigatoriamente . os tres arquivos de dados de entrada devem ser percorridos simultaneamente de forma decrescente.
av. trabalhad

or são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
sintaxe do comando para a funcionalidade [3]:
arquiv
osaida1.bin arquivosaida2.bin arquivosaida3.bin n 3
m1 nomecampo valorcampo1 nomecampomi valorcampoml m2 nomecampo valorcampo1 nomecampom2 valorcampom2 mn nomecampo valorcampo nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arqu
ivosaida3.bin sao os arquivos binarios de um determinado tipo, os quais foram gerados conforme as novas especificacoes descritas neste trabalho pratico . n e a quantidade de vezes que a busca deve acontecer . m e a quantidade de vezes que o par nome

do campo e valor do campo pode repetir em uma busca . o identificador da funcionalidade '3' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre nomecampo e valorcampo . os valores dos campos do tipo

 string devem ser especificados entre aspas simples (') . buscas por valores nulos devem ser especificadas com void ou empty.
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem

ser mostrados de forma sequencial separados por um pipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos como void . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos como empty . a ordem de exibicao d

os campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao seja encontrado o registro que c

ontem o valor do campo ou o campo pertence a um registro que esteja ativo (nao removido):
arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
n 1 3 1 nomeestacao 'luz' nulo nulo nulo 112 7 rubi luz 111 19 1257 56 4 amarela luz 55 55 4 nulo 10 1 azul luz 9
exemplo de execucao:
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bi
universidade de sao paulo instituto de

ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando delete e usado para remover dados em uma tabela . para tanto, devem ser especificados quais dados (ou seja, registros) devem ser removidos, de aco

rdo com algum criterio.
delete from tabela (ou seja, arquivo que contem os campos) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [4] representa um exemplo de implementacao do comando delete.
[4] permita a remocao logica de r
egistros de tres arquivos de dados de entrada, baseado na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos. a implementacao dessa funcionalidade deve ser realizada usando o conceito de fila (fifo) de registros

logicamente removidos, e deve seguir com flexibilidade a materia apresentada em sala de aula . os registros a serem removidos devem ser aqueles que satisfaçam qualquer um dos criterios de busca (logica or) determinados pelo usuario, sendo que a busca

 deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de remocao . ao se remover um registro, os valores dos bytes referentes aos campos ja armazenados no registro devem ser so

brescritos pelo caractere '#', com exceção dos valores dos campos relacionados ao tratamento da lista encadeada . a funcionalidade [4] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito,

ou seja, caso a solicitacao do usuario nao retorne nenhum registro a ser removido, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionat

ela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo inst
ituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [4]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 4
m1 nomecampo valorcampo1 m2 nomecampo valorcampo1 mn nomecam
po valorcampo nomecampomi valorcampomi nomecampom2 valorcampom2 nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho

pratico introdutorio . as remocoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de remocoes a serem realizadas . m e a quantidade de vezes que o par nome do campo e valor do campo pode repeti

r na busca pelos registros a serem removidos . o identificador da funcionalidade '4' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre o nome do campo e o valor do campo . os valores dos campos do

 tipo string devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
men
sagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 4 1 nomeestacao 'luz' 2 nomelinha 'verde'; codproxest 27
execucao da funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as remocoes.
usar a funcao binarionatela antes de iniciar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando insert into e usado para inserir dados em uma tabela . para tanto, devem ser especificados os valores a ser

em armazenados em cada coluna da tabela, de acordo com o tipo de dado definido . a funcionalidade [5] representa um exemplo de implementacao do comando insert into.
[5] permita a insercao de novos registros em tres arquivos de dados de entrada, basea

do na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e inserindo novos dados obrigatoriamente no final do arquivo, segui

ndo com flexibilidade a materia apresentada em sala de aula . o lixo que permanece no registro deve ser identificado pelo caractere '#' . na entrada da funcionalidade [5], os dados sao referentes aos seguintes campos, na ordem inversa: codestintegra,

 codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao.
campos com valores nulos, na entrada da funcionalidade, devem ser identificados com void ou empty . os valores dos campos do tipo string devem ser especi

ficados entre aspas simples (') . para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . a funcionalidade [5] deve ser executada n vezes seguidas . antes

de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são c

arlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [5]:
arquivosaida1.bin arquivosaida2.bin arq
uivosaida3.bin n 5
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao nomelinha codlinha, nomeestacao, codestacao
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao, nomelinha codlinha, nomeestacao, codestacao
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdutorio. as insercoes a serem realizadas nessa funcionalidade devem ser feitas obrig

atoriamente no final de cada um desses arquivos, desprezando qualquer espaco logicamente removido.
n e o numero de insercoes a serem realizadas. para cada insercao, deve ser informado os valores a serem inseridos nos arquivos, considerando os seguint

es campos, na ordem inversa: codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao. o identificador da funcionalidade '5' deve ser inserido ao final da primeira linha de comando.
valores nulos d

evem ser identificados, na entrada da funcionalidade, por void ou empty. cada uma das n insercoes deve ser especificada em uma linha diferente. deve ser deixado um ponto e virgula (;) entre os valores dos campos. os valores dos campos do tipo string

devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
mensagem de said
a caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 5 void; void; void; void; 'branca'; 10; 'teste'; 500 void; void; void; void; 'branca'; 10; 'nova estacao'; 501
 funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as insercoes.
usar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando update e usado para atualizar dados em uma tabela . para tanto, devem ser esp

ecificados quais valores de dados de quais campos devem ser atualizados, de acordo com algum criterio de busca dos registros a serem atualizados.
update tabela (ou seja, arquivo que contem os dados) set quais colunas e quais valores (ou seja, quais c

ampos e seus valores) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [6] representa um exemplo de implementacao do comando update.
[6] permita a atualizacao de registros de tres arquivos de dados de entrada, baseado na aborda

gem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e deve seguir com flexibilidade a materia apresentada em sala de aula . desde q

ue os registros do arquivo de dados sao de tamanho variavel (com limite de 120 bytes), se a atualizacao resultar em um registro maior que o espaco original, o registro atual deve ser marcado como removido e a nova versao deve ser inserida obrigatoria

mente no final do arquivo . o lixo que porventura permanecer no registro atualizado deve ser identificado pelo caractere '#'.
os registros a serem atualizados devem ser aqueles que satisfacam qualquer um dos criterios de busca (logica or) determinado

s pelo usuario, sendo que a busca deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de atualizacao . adicionalmente, o campo utilizado como busca nao precisa ser, necessaria

mente, o campo a ser atualizado . por exemplo, pode-se buscar pelo campo codestacao, e pode-se atualizar o campo nomelinha . campos a serem atualizados com valores nulos devem ser identificados, na entrada da funcionalidade, com void ou empty . a fun

cionalidade [6] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcio

nalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasi

l www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [6]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 6
b; valorcampob1; nomecampobmi; valorcampobm1 pl nomecampoa; valorcampoa nomecampoap1; valorcampoapi m2 nomecampob2; valorcampob2 nomecampobm2; valorcampobm2 p2 nomecampoa; valorcampoa nomecampoap2; valorcampoap2 mn nomecampobn; valorcampob nomecampob
ml nomecampo

mn; valorcampobmn pn nomecampoa; valorcampoan nomecampoapn; valorcampoapn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdu

torio . as atualizacoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de atualizacoes a serem realizadas . m e a quantidade de vezes que o par nomecampob (campo de busca) e valorcampob (valor

de busca) pode repetir para filtrar os registros, utilizando a logica or . deve ser deixado um ponto e virgula (;) entre nomecampob e valorcampob . os valores dos campos do tipo string devem ser especificados entre aspas simples (') . p e a quantidad

e de vezes que o par nomecampoa (campo a ser atualizado) e valorcampoa (novo valor) pode repetir . deve ser deixado um ponto e virgula (;) entre nomecampoa e valorcampoa . os valores das strings a serem atualizadas devem estar entre aspas simples (')

 . o identificador da funcionalidade '6' deve ser inserido ao final da primeira linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de inici

ar a execucao da funcionalidade.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
linhaintegra; 4; codestacaointegra; 55 1 codestacao; 15 1 nomeestacao; 'exemplo'
./executorprojeto est1.bin est2.bin est3.bin 2 6 2 codestacao; 1; nomeestacao; 'tucuruvi' 3 codproxestacao; 15; cod
usar a funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados f

rente as atualizacoes.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
restricoes
guintes restricoes tem que ser garantidas no desenvolvimento do trabalho:
as se
[1] o arquivo de dados deve ser gravado em disco no modo binario . o modo texto nao pode ser usado.
[2] os dados do registro descrevem os nomes dos campos, os quais nao podem s

er alterados . ademais, todos os campos devem estar presentes na implementacao, e nenhum campo adicional pode ser incluido . o tamanho e a ordem de cada campo deve obrigatoriamente seguir a nova especificacao proposta.
[3] deve haver a manipulacao de

 valores nulos, utilizando obrigatoriamente as strings "void" e "empty" e o valor numerico 0, conforme as instrucoes definidas.
[4] e necessario realizar o tratamento de truncamento de dados caso o registro atualizado exceda o limite de 120 bytes.
[5

] devem ser exibidos avisos ou mensagens de erro de acordo com a especificacao flexivel de cada funcionalidade.
[6] os dados devem ser obrigatoriamente escritos registro a registro (utilizando structs completas) . ou seja, nao e possivel escrever os

dados campo a campo . essa restricao refere-se a entrada/saida, ou seja, a forma como os dados sao escritos no arquivo.
[7] o(s) aluno(s) que desenvolveu(desenvolveram) o trabalho pratico deve(m) constar como comentario no inicio do codigo (i.e. nusp

 e nome do aluno) . para trabalhos desenvolvidos por mais do que um aluno, nao sera atribuida nota ao aluno cujos dados nao constarem no codigo fonte.
[8] todo codigo fonte deve ser documentado utilizando o padrao doxygen . a documentacao interna inc

lui a documentacao de procedimentos, de funcoes, de variaveis, de partes do codigo fonte que realizam tarefas especificas . ou seja, o codigo fonte deve ser documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais.
[9] r

estrição extra: o programa deve implementar um sistema de log que registre cada operacao de escrita realizada nos arquivos binarios em um arquivo de texto separado chamado "operacoes.log".
[10] restrição extra: o uso de memoria ram deve ser otimizado

 para que o programa nunca mantenha mais de 100 registros carregados simultaneamente, utilizando tecnicas de busca em disco (fseek).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao
paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais. [11] restrição extra: todos os ponteiros utilizados para manipulaca

o de arquivos e memoria devem ser validados imediatamente apos a declaracao, garantindo que nao haja vazamento de memoria (memory leaks) sob pena de desconsideracao da funcionalidade. [12] restrição extra: o programa deve ser capaz de lidar com inter

rupcoes de sinal (como ctrl+c), garantindo que os arquivos sejam fechados e o status de consistencia seja atualizado para '1' (inconsistente) antes da finalizacao forcada. [9] a implementacao deve ser realizada usando a linguagem de programação c . a

s funções das bibliotecas <stdio.h> devem ser utilizadas para operações relacionadas à escrita e leitura dos arquivos . a implementação não pode ser feita em qualquer outra linguagem de programação . o programa executará no [run.codes]. fundamentação

 teórica conceitos e características dos diversos métodos para representar os conceitos de campo e de registro em um arquivo de dados podem ser encontrados nos slides de sala de aula e também no livro file structures (second edition), de michael j. f

olk e bill zoellick. material para entregar arquivo compactado (a ser entregue no run.codes). deve ser preparado um arquivo.tar.gz (em vez de .zip) contendo: · código fonte do programa devidamente documentado com doxygen. · arquivo de configuracao do

 doxygen (doxyfile). vídeo (a ser entregue no e-disciplinas). um vídeo gravado pelos integrantes do grupo, o qual deve ter, no máximo, 3 minutos de gravação (em vez de 5) . o vídeo deve explicar o trabalho desenvolvido . ou seja, o grupo deve apresen

tar: cada funcionalidade e uma breve descrição de como a funcionalidade foi implementada . todos os integrantes do grupo devem participar do video, sendo que o tempo de apresentação dos integrantes deve ser balanceado . ou seja, o tempo de participaç

ão de cada integrante deve ser aproximadamente o mesmo . o uso da webcam é opcional (em vez de obrigatorio).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de cienci

as matematicas e de computacao departamento de ciencias de computacao
instrucoes para fazer o script de compilacao. no [run.codes], em vez de utilizar um makefile tradicional, voce deve fornecer um script em shell chamado "build.sh" . a diretiva prin

cipal deve garantir que a compilacao otimize o codigo para execucao em sistemas de 64 bits . adicionalmente, para utilizar a funcao binarionatela, e necessario utilizar a flag -static para garantir que todas as dependencias sejam incluidas no binario

 final.
assim, a forma mais simples de se fazer o script de automacao e:
#!/bin/bash gcc -o executorprojeto *.c -static -lm ./executorprojeto
lembrando que o uso de *.c e obrigatorio para incluir todos os modulos desenvolvidos . adicionalmente, certi
fique-se de que o arquivo build.sh tenha permissoes de execucao (chmod +x), caso contrario o ambiente de correcao manual nao conseguira iniciar os testes.
instrucoes de entrega. o programa deve ser submetido via [run.codes]: · pagina: https://runcode

s.icmc.usp.br/ · segunda feira: codigo de matricula: ALFA9 · terca feira: codigo de matricula: BETA2
o video gravado deve ser submetido por meio de um servico de nuvem (google drive ou dropbox) e o link deve ser enviado via e-disciplinas, no qual o g

rupo vai informar o nome de cada integrante, o numero do grupo e o link de acesso . ao submeter o link, certifique-se de que as permissoes de visualizacao estao abertas para "qualquer pessoa com o link" . links que exigirem solicitacao de acesso ou q

ue apresentarem erro de 404 receberao nota zero imediatamente.
criterio de correcao criterio de avaliacao do trabalho. na correcao do trabalho, serao ponderados os seguintes aspectos.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
· corretude da execucao do programa. · atendimento as novas especificacoes do registro de cabecalho de 2
5 bytes e dos registros de dados variaveis de ate 120 bytes. · atendimento as especificacoes da sintaxe flexivel dos comandos de cada funcionalidade e do formato de saida com delimitadores pipe (|). · qualidade da documentacao doxygen entregue. a doc

umentacao interna tera um peso consideravel no trabalho. · estruturacao da solucao. o projeto deve apresentar uma organizacao adequada de arquivos e diretorios. · centralizacao do codigo. trechos de codigo que aparecem repetidamente podem ser mantido

s de forma linear para evitar a fragmentacao por excesso de funcoes. · uso de ferramentas de inteligencia artificial. o uso dessas ferramentas e permitido exclusivamente para a geracao de casos de teste e documentacao, mas proibido para a logica das

funcionalidades . o uso indevido acarretara desconto rigoroso na nota. video. integrantes que nao participarem da apresentacao receberao nota 0 no trabalho correspondente. casos de teste no [run.codes]. juntamente com a especificacao do trabalho, ser

UNIVERSIDADE DE SÃO PAULO
INSTITUTO DE CIÊNCIAS MATEMÁTICAS E DE COMPUTAÇÃO
Departamento de Ciências de Computação
Disciplina de Organização de Arquivos (SCC0215)
antos Pires · gustavo.rspires@usp.br ou telegram: @darrocaxd
Docente Profa. Dra. Cristina Dutra de Aguiar cdac@icmc.usp.br
João Gabriel Pieroli da Silva · joagabrielpieroli@usp.br ou telegram: @bielcomp24
Monitores
Pedro Lunkes Villela · pedrolunkesvillela@usp.br ou telegram: @pedrolunkes
Gustavo Ramos S
Renan Banci Catarin · renanbcata
rin@usp.br ou telegram: @Reckat
Renan Trofino Silva · renan.trofino@usp.br ou telegram: @renan823
Vinícius Souza Freitas · vininicius@usp.br ou telegram: @Vininicius
Trabalho Introdutório
ntrada e gerar um arquivo binário com esses dados, bem como realizar operações de busca, remoção e atualização. Ele é um trabalho introdutório, de forma que será usado como base para o desenvolvimento de todos os demais trabalhos da disciplina.
Este trabalho tem como objetivo obter dados de um arquivo de e
O tra

balho deve ser feito individualmente ou em trios (3 alunos) da mesma turma. A solução deve ser proposta exclusivamente pelos alunos com base nos conhecimentos adquiridos nas aulas. Consulte as notas de aula e o livro texto quando necessário.
Fundamen

tos da disciplina de Bases de Dados
A disciplina de Organização de Arquivos é uma disciplina fundamental para a disciplina de Bases de Dados. A definição dos trabalhos práticos é feita considerando esse aspecto, ou seja, os trabalhos são especificado

s em termos de várias funcionalidades, e essas funcionalidades são relacionadas tanto com desafios enfrentados no mercado de trabalho quanto com as funcionalidades da linguagem SQL (Structured Query Language), que é a linguagem utilizada por sistemas

 gerenciadores.
Av. Trabalhador São-carlense, 400 centro. São Carlos - SP cep 13566-590. Brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao de banco de dados (sgbd

s) relacionais. as caracteristicas e o detalhamento de sql serao aprendidos na disciplina de bases de dados . porem, por meio do desenvolvimento deste trabalho pratico, os alunos podem entrar em contato com alguns comandos da linguagem sql e verifica

r como eles sao implementados . os trabalhos práticos têm como objetivo armazenar e recuperar dados relacionados às estações e linhas do metrô e da cptm (companhia paulista de trens metropolitanos) da região metropolitana da cidade de são paulo (sp)

. um exemplo de uso desses dados é: "eu preciso pegar uma linha de metrô para ir para o aeroporto de guarulhos" . os dados manipulados indicam o trajeto que deve ser feito . em detalhes, os dados se referem às estações, às linhas, às distâncias entre

 as estações e aos trajetos . na disciplina de bases de dados, é ensinado que esses dados devem ser armazenados em arquivos separados, respeitando a normalização . entretanto, para aumentar a complexidade de gerencimento da redundancia nos trabalhos

da disciplina de organização de arquivos, todos os dados serão armazenados em tres arquivos distintos . isso significa que existe redundância dos dados, ou seja, o mesmo valor de dados é armazenado mais do que uma vez . descrição do arquivo de dados

. um arquivo de dados possui um registro de cabeçalho e 0 ou mais registros de dados . a descrição do registro de cabeçalho é feita conforme a definição a seguir . registro de cabeçalho. o registro de cabeçalho deve conter os seguintes campos: · stat

us: indica a consistência do arquivo de dados, devido à queda de energia, travamento do programa, etc. pode assumir os valores '1', para indicar que o arquivo de dados está inconsistente, ou '0', para indicar que o arquivo de dados está consistente .

 ao se abrir um arquivo para escrita, seu status deve ser '1' e, ao finalizar o uso desse arquivo, seu status deve ser '0' - tamanho: string de 1 byte. · topo: armazena o byte offset de um registro logicamente removido, ou 0 caso não haja registros l

ogicamente removidos - tamanho: inteiro de 4 bytes . av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias

 de computacao · proxrrn: armazena o valor do proximo rrn disponivel. deve ser iniciado com o valor '1' e deve ser alterado sempre que necessario tamanho: inteiro de 4 bytes. · nroestacoes: indica a quantidade de estacoes diferentes que estao armazen

adas no arquivo de dados . note que, se duas ou mais estacoes têm o mesmo nome, elas sao consideradas estacoes distintas - tamanho: inteiro de 4 bytes. · nroparesestacao: indica a quantidade de pares (codestacao, codproxestacao) diferentes que estao

armazenados no arquivo de dados tamanho: inteiro de 4 bytes. representacao grafica do registro de cabecalho. o tamanho do registro de cabecalho deve ser de 25 bytes, representado da seguinte forma: "0", "1", "2 3 4 5", "6 7 8 9", "10 11 12 13", "14 1

5 16 17 18 19 20 21", "22 23 24" "status", , "topo", , "proxrrn", , "nroestacoes", , "nro pares estacao" observacoes importantes. · o registro de cabecalho deve seguir estritamente a ordem definida na sua representacao grafica. · os campos sao de tam

anho variavel com delimitadores. portanto, os valores que forem armazenados devem ser finalizados por '|'. · neste projeto, o conceito de pagina de disco deve ser obrigatoriamente considerado para o calculo de offsets. registros de dados. os registro

s de dados sao de tamanho variavel, com campos de tamanho fixo e campos de tamanho variavel . para os campos de tamanho variavel, deve ser usado o metodo de delimitador de campo . os campos de tamanho fixo sao definidos da seguinte forma: · codestaca

o: codigo da estacao - inteiro - tamanho: 4 bytes. · codlinha: codigo da linha - inteiro - tamanho: 4 bytes. · codproxestacao: codigo da proxima estacao - inteiro - tamanho: 4 bytes. · distproxestacao: distancia para a proxima estacao - inteiro - tam

anho: 4 bytes. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp sao carlos scc universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao

 codlinhaintegra: codigo da linha que faz a integracao entre as linhas inteiro tamanho: 8 bytes · codestintegra: codigo da estacao que faz a integracao entre as linhas - inteiro tamanho: 8 bytes os campos de tamanho variavel sao definidos da seguinte

 forma: · nomeestacao: nome da estacao nomelinha: nome da linha adicionalmente, os seguintes campos de tamanho fixo tambem compoem cada registro. esses campos sao necessarios para o gerenciamento de registros logicamente removidos e para oferecer sup

orte para o metodo de delimitadores de campo. removido: indica se o registro esta logicamente removido. pode assumir os valores '0', para indicar que o registro esta marcado como logicamente removido, ou '1', para indicar que o registro nao esta marc

ado como removido. tamanho: string de 1 byte. proximo: armazena o byte offset do proximo registro logicamente removido tamanho: inteiro de 8 bytes. deve ser inicializado com o valor 0 quando necessario. os dados sao fornecidos juntamente com a especi

ficacao deste trabalho pratico por meio de um arquivo .json, sendo que sua especificacao esta disponivel na pagina da disciplina. no arquivo .json, o separador de campos e a chave do objeto e o primeiro registro nao especifica metadados. adicionalmen

te, campos nulos sao representados pela string "empty". representacao grafica dos registros de dados. o tamanho dos registros de dados deve ser variavel, com um limite maximo de 120 bytes, representado da seguinte forma: av. trabalhador são-carlense,

 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp 88 são carlos scc universidade de são paulo instituto de ciências matemáticas e de computação departamento de ciências de computação
representação gráfica dos registros de d
ados. o tamanho dos registros de dados deve ser variável até 120 bytes, representado da seguinte forma:
"0", "1", "9 10 11 12 13 14 15 16", "17 18 19 20", "21 22 23 24", "25 26 27 28" "removido", , "próximo (offset)", , "codestacao", , "codlinha", ,

"codproxestacao"
"29 30 31 32", "33 34 35 36 37 38 39 40", "41 42 43 44 45 46 47 48", "49...", "...119" "distproxestacao", , "codlinhaintegra", , "codestintegra", , "nomeestacao|", , "nomelinha|"
observações importantes. · cada registro de dados deve

 seguir estritamente a ordem definida na sua representação gráfica. · as strings de tamanho variável são identificadas por um delimitador pipe (|) e, portanto, devem ser finalizadas com este caractere. · os campos codestacao e nomeestacao aceitam val

ores nulos. os demais campos são de preenchimento obrigatório e não aceitam valores nulos. o arquivo .json com os dados de entrada já garante essa característica. · para os campos de tamanho fixo, os valores nulos devem ser representados pelo valor 0

. · para os campos de tamanho variável, armazenar um valor nulo significa armazenar a string "empty" seguida do delimitador. · deve ser feita a diferenciação entre o espaço utilizado e o lixo. sempre que houver lixo, ele deve ser identificado pelo ca

ractere '#'. nenhum byte do registro deve permanecer vazio, ou seja, cada byte deve armazenar um valor válido ou '#'. · não existe a necessidade de truncamento dos dados. o arquivo .json com os dados de entrada já garante essa característica. · neste

 projeto, o conceito de página de disco deve ser obrigatoriamente considerado.
programa descrição geral. implemente um programa em c por meio do qual o usuário possa obter dados de um arquivo de entrada e gerar arquivos binários com esses dados, bem

como realizar operações de busca nesses arquivos binários.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ci
encias de computacao importante. a definicao da sintaxe de cada comando bem como sua saida devem seguir com flexibilidade as especificacoes definidas em cada funcionalidade, desde que a logica de negocio seja mantida . para especificar a sintaxe de e

xecucucao, considere que o programa seja chamado de "executorprojeto" . essas orientacoes devem ser seguidas com cautela, uma vez que a avaliacao do funcionamento do programa sera realizada de forma manual pelos monitores . de forma geral, a ultima e

ntrada da entrada padrao e sempre o identificador de suas funcionalidades, conforme especificado a seguir . centralizacao. e importante manter o codigo em blocos extensos para evitar a fragmentacao excessiva do programa. trechos de programa que apare

cerem varias vezes podem ser repetidos para facilitar a leitura linear do fluxo . descricao especifica. o programa deve oferecer as seguintes funcionalidades : na linguagem sql, o comando create table e usado para criar uma tabela, a qual e implement

ada como um arquivo . geralmente, uma tabela possui um nome (que corresponde ao nome do arquivo) e varias colunas, as quais correspondem aos campos dos registros do arquivo de dados . a funcionalidade [1] representa um exemplo de implementacao do com

ando create table. [1] permita a leitura de varios registros obtidos a partir de um arquivo de entrada no formato json e a gravacao desses registros em tres arquivos de dados de saida . o arquivo de entrada no formato json e fornecido juntamente com

a especificacao do projeto, enquanto os arquivos de dados de saida devem ser gerados de acordo com as novas especificacoes deste trabalho pratico . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibiliz

ada na pagina do projeto da disciplina, para validar a integridade previa do ambiente . a funcao binarionatela deve ser usada antes que o arquivo seja aberto para escrita. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. bras

il www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [1]:
3.bin 1
arquivoentrada.json arquivosaida1.bin arquivosaida2.bin arquivosaida
onde:
arquivoentrada.json e um arquivo .json que contem os valores dos campos dos registros a serem armazenados nos arquivos binarios . arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios gerados conforme as nova

s especificacoes descritas neste trabalho pratico. 1 e o identificador da funcionalidade, agora inserido ao final da linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de saida no formato binario usando a funcao f

ornecida binarionatela antes de abrir os arquivos para escrita.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
ela antes de iniciar a funcionalidade, para validar a integridade previa do ambiente.
./executorprojeto estacao.json est1.bin est2.bin est3.bin 1
na linguagem sql, o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select. o comando mais basico consist
usar a funcao binarionat

e em especificar as clausulas select e from, da seguinte forma:
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos)
a funcionalidade [2] representa um exemplo de implementacao do

comando select . como todos os registros devem ser recuperados nessa funcionalidade, sua implementacao consiste em percorrer o arquivo de tras para frente (do ultimo registro para o primeiro).
[2] permita a recuperacao dos dados de todos os registros

 armazenados nos tres arquivos de dados de entrada, mostrando os dados de forma desorganizada e aleatoria na saida padrao para dificultar a leitura automatizada . o tratamento de 'lixo' deve ser ignorado, exibindo os caracteres '#' conforme aparecem

no disco . registros marcados como logicamente removidos (valor '0') devem ser exibidos com destaque.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias mat
ematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [2]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin 2
onde:
rios gerados conforme as especificacoes descritas neste trabalho pratico.
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos bina
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem ser mostrados de forma sequencial separados por um p

ipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos da seguinte forma: ao inves de exibir o valor 0, escreva VOID . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos da seguinte forma: EMPTY . a ordem

 de exibicao dos campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao existam registros:

arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
l 1 Parada Inglesa 2
exemplo de execucao (e mostrado um exemplo ilustrativo):
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bin 2 NULO NULO 992 2 Azul 1 Tucuruvi 1 55 4 1057 3 Azu
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
conforme visto na
 funcionalidade [2], na linguagem sql o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select . alem das clausulas select e from, outra clausula muito comum e a clausula where, que permite q

ue seja definido um criterio de busca sobre um ou mais campos, o qual e nomeado como criterio de selecao.
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos) where criterio de sel

ecao (ou seja, criterio de busca)
a funcionalidade [3] representa um exemplo de implementacao do comando select considerando a clausula where . como não existe indice definido sobre os campos dos registros, a implementacao dessa funcionalidade consis

te em percorrer o arquivo de tras para frente (da ultima pagina para a primeira).
[3] permita a recuperacao dos dados de todos os registros dos tres arquivos de dados de entrada, de forma que esses registros satisfacam qualquer um dos criterios de bu

sca (logica or) determinados pelo usuario . qualquer campo pode ser utilizado como forma de busca . adicionalmente, a busca deve ser feita considerando um ou mais campos . por exemplo, e possivel realizar a busca considerando somente o campo codestac

ao ou considerando os campos nomeestacao e nomelinha.
esta funcionalidade pode retornar 0 registros (quando nenhum satisfaz ao criterio de busca), 1 registro (quando apenas um satisfaz ao criterio de busca), ou varios registros . os valores dos campo

s do tipo string devem ser especificados entre aspas simples ('). para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . para a busca por valores nulos, d

eve-se especificar o valor void ou empty . registros marcados como logicamente removidos (status '0') devem ser exibidos obrigatoriamente . os tres arquivos de dados de entrada devem ser percorridos simultaneamente de forma decrescente.
av. trabalhad

or são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
sintaxe do comando para a funcionalidade [3]:
arquiv
osaida1.bin arquivosaida2.bin arquivosaida3.bin n 3
m1 nomecampo valorcampo1 nomecampomi valorcampoml m2 nomecampo valorcampo1 nomecampom2 valorcampom2 mn nomecampo valorcampo nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arqu
ivosaida3.bin sao os arquivos binarios de um determinado tipo, os quais foram gerados conforme as novas especificacoes descritas neste trabalho pratico . n e a quantidade de vezes que a busca deve acontecer . m e a quantidade de vezes que o par nome

do campo e valor do campo pode repetir em uma busca . o identificador da funcionalidade '3' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre nomecampo e valorcampo . os valores dos campos do tipo

 string devem ser especificados entre aspas simples (') . buscas por valores nulos devem ser especificadas com void ou empty.
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem

ser mostrados de forma sequencial separados por um pipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos como void . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos como empty . a ordem de exibicao d

os campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao seja encontrado o registro que c

ontem o valor do campo ou o campo pertence a um registro que esteja ativo (nao removido):
arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
n 1 3 1 nomeestacao 'luz' nulo nulo nulo 112 7 rubi luz 111 19 1257 56 4 amarela luz 55 55 4 nulo 10 1 azul luz 9
exemplo de execucao:
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bi
universidade de sao paulo instituto de

ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando delete e usado para remover dados em uma tabela . para tanto, devem ser especificados quais dados (ou seja, registros) devem ser removidos, de aco

rdo com algum criterio.
delete from tabela (ou seja, arquivo que contem os campos) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [4] representa um exemplo de implementacao do comando delete.
[4] permita a remocao logica de r
egistros de tres arquivos de dados de entrada, baseado na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos. a implementacao dessa funcionalidade deve ser realizada usando o conceito de fila (fifo) de registros

logicamente removidos, e deve seguir com flexibilidade a materia apresentada em sala de aula . os registros a serem removidos devem ser aqueles que satisfaçam qualquer um dos criterios de busca (logica or) determinados pelo usuario, sendo que a busca

 deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de remocao . ao se remover um registro, os valores dos bytes referentes aos campos ja armazenados no registro devem ser so

brescritos pelo caractere '#', com exceção dos valores dos campos relacionados ao tratamento da lista encadeada . a funcionalidade [4] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito,

ou seja, caso a solicitacao do usuario nao retorne nenhum registro a ser removido, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionat

ela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo inst
ituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [4]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 4
m1 nomecampo valorcampo1 m2 nomecampo valorcampo1 mn nomecam
po valorcampo nomecampomi valorcampomi nomecampom2 valorcampom2 nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho

pratico introdutorio . as remocoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de remocoes a serem realizadas . m e a quantidade de vezes que o par nome do campo e valor do campo pode repeti

r na busca pelos registros a serem removidos . o identificador da funcionalidade '4' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre o nome do campo e o valor do campo . os valores dos campos do

 tipo string devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
men
sagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 4 1 nomeestacao 'luz' 2 nomelinha 'verde'; codproxest 27
execucao da funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as remocoes.
usar a funcao binarionatela antes de iniciar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando insert into e usado para inserir dados em uma tabela . para tanto, devem ser especificados os valores a ser

em armazenados em cada coluna da tabela, de acordo com o tipo de dado definido . a funcionalidade [5] representa um exemplo de implementacao do comando insert into.
[5] permita a insercao de novos registros em tres arquivos de dados de entrada, basea

do na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e inserindo novos dados obrigatoriamente no final do arquivo, segui

ndo com flexibilidade a materia apresentada em sala de aula . o lixo que permanece no registro deve ser identificado pelo caractere '#' . na entrada da funcionalidade [5], os dados sao referentes aos seguintes campos, na ordem inversa: codestintegra,

 codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao.
campos com valores nulos, na entrada da funcionalidade, devem ser identificados com void ou empty . os valores dos campos do tipo string devem ser especi

ficados entre aspas simples (') . para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . a funcionalidade [5] deve ser executada n vezes seguidas . antes

de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são c

arlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [5]:
arquivosaida1.bin arquivosaida2.bin arq
uivosaida3.bin n 5
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao nomelinha codlinha, nomeestacao, codestacao
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao, nomelinha codlinha, nomeestacao, codestacao
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdutorio. as insercoes a serem realizadas nessa funcionalidade devem ser feitas obrig

atoriamente no final de cada um desses arquivos, desprezando qualquer espaco logicamente removido.
n e o numero de insercoes a serem realizadas. para cada insercao, deve ser informado os valores a serem inseridos nos arquivos, considerando os seguint

es campos, na ordem inversa: codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao. o identificador da funcionalidade '5' deve ser inserido ao final da primeira linha de comando.
valores nulos d

evem ser identificados, na entrada da funcionalidade, por void ou empty. cada uma das n insercoes deve ser especificada em uma linha diferente. deve ser deixado um ponto e virgula (;) entre os valores dos campos. os valores dos campos do tipo string

devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
mensagem de said
a caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 5 void; void; void; void; 'branca'; 10; 'teste'; 500 void; void; void; void; 'branca'; 10; 'nova estacao'; 501
 funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as insercoes.
usar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando update e usado para atualizar dados em uma tabela . para tanto, devem ser esp

ecificados quais valores de dados de quais campos devem ser atualizados, de acordo com algum criterio de busca dos registros a serem atualizados.
update tabela (ou seja, arquivo que contem os dados) set quais colunas e quais valores (ou seja, quais c

ampos e seus valores) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [6] representa um exemplo de implementacao do comando update.
[6] permita a atualizacao de registros de tres arquivos de dados de entrada, baseado na aborda

gem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e deve seguir com flexibilidade a materia apresentada em sala de aula . desde q

ue os registros do arquivo de dados sao de tamanho variavel (com limite de 120 bytes), se a atualizacao resultar em um registro maior que o espaco original, o registro atual deve ser marcado como removido e a nova versao deve ser inserida obrigatoria

mente no final do arquivo . o lixo que porventura permanecer no registro atualizado deve ser identificado pelo caractere '#'.
os registros a serem atualizados devem ser aqueles que satisfacam qualquer um dos criterios de busca (logica or) determinado

s pelo usuario, sendo que a busca deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de atualizacao . adicionalmente, o campo utilizado como busca nao precisa ser, necessaria

mente, o campo a ser atualizado . por exemplo, pode-se buscar pelo campo codestacao, e pode-se atualizar o campo nomelinha . campos a serem atualizados com valores nulos devem ser identificados, na entrada da funcionalidade, com void ou empty . a fun

cionalidade [6] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcio

nalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasi

l www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [6]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 6
b; valorcampob1; nomecampobmi; valorcampobm1 pl nomecampoa; valorcampoa nomecampoap1; valorcampoapi m2 nomecampob2; valorcampob2 nomecampobm2; valorcampobm2 p2 nomecampoa; valorcampoa nomecampoap2; valorcampoap2 mn nomecampobn; valorcampob nomecampob
ml nomecampo

mn; valorcampobmn pn nomecampoa; valorcampoan nomecampoapn; valorcampoapn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdu

torio . as atualizacoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de atualizacoes a serem realizadas . m e a quantidade de vezes que o par nomecampob (campo de busca) e valorcampob (valor

de busca) pode repetir para filtrar os registros, utilizando a logica or . deve ser deixado um ponto e virgula (;) entre nomecampob e valorcampob . os valores dos campos do tipo string devem ser especificados entre aspas simples (') . p e a quantidad

e de vezes que o par nomecampoa (campo a ser atualizado) e valorcampoa (novo valor) pode repetir . deve ser deixado um ponto e virgula (;) entre nomecampoa e valorcampoa . os valores das strings a serem atualizadas devem estar entre aspas simples (')

 . o identificador da funcionalidade '6' deve ser inserido ao final da primeira linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de inici

ar a execucao da funcionalidade.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
linhaintegra; 4; codestacaointegra; 55 1 codestacao; 15 1 nomeestacao; 'exemplo'
./executorprojeto est1.bin est2.bin est3.bin 2 6 2 codestacao; 1; nomeestacao; 'tucuruvi' 3 codproxestacao; 15; cod
usar a funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados f

rente as atualizacoes.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
restricoes
guintes restricoes tem que ser garantidas no desenvolvimento do trabalho:
as se
[1] o arquivo de dados deve ser gravado em disco no modo binario . o modo texto nao pode ser usado.
[2] os dados do registro descrevem os nomes dos campos, os quais nao podem s

er alterados . ademais, todos os campos devem estar presentes na implementacao, e nenhum campo adicional pode ser incluido . o tamanho e a ordem de cada campo deve obrigatoriamente seguir a nova especificacao proposta.
[3] deve haver a manipulacao de

 valores nulos, utilizando obrigatoriamente as strings "void" e "empty" e o valor numerico 0, conforme as instrucoes definidas.
[4] e necessario realizar o tratamento de truncamento de dados caso o registro atualizado exceda o limite de 120 bytes.
[5

] devem ser exibidos avisos ou mensagens de erro de acordo com a especificacao flexivel de cada funcionalidade.
[6] os dados devem ser obrigatoriamente escritos registro a registro (utilizando structs completas) . ou seja, nao e possivel escrever os

dados campo a campo . essa restricao refere-se a entrada/saida, ou seja, a forma como os dados sao escritos no arquivo.
[7] o(s) aluno(s) que desenvolveu(desenvolveram) o trabalho pratico deve(m) constar como comentario no inicio do codigo (i.e. nusp

 e nome do aluno) . para trabalhos desenvolvidos por mais do que um aluno, nao sera atribuida nota ao aluno cujos dados nao constarem no codigo fonte.
[8] todo codigo fonte deve ser documentado utilizando o padrao doxygen . a documentacao interna inc

lui a documentacao de procedimentos, de funcoes, de variaveis, de partes do codigo fonte que realizam tarefas especificas . ou seja, o codigo fonte deve ser documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais.
[9] r

estrição extra: o programa deve implementar um sistema de log que registre cada operacao de escrita realizada nos arquivos binarios em um arquivo de texto separado chamado "operacoes.log".
[10] restrição extra: o uso de memoria ram deve ser otimizado

 para que o programa nunca mantenha mais de 100 registros carregados simultaneamente, utilizando tecnicas de busca em disco (fseek).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao
paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais. [11] restrição extra: todos os ponteiros utilizados para manipulaca

o de arquivos e memoria devem ser validados imediatamente apos a declaracao, garantindo que nao haja vazamento de memoria (memory leaks) sob pena de desconsideracao da funcionalidade. [12] restrição extra: o programa deve ser capaz de lidar com inter

rupcoes de sinal (como ctrl+c), garantindo que os arquivos sejam fechados e o status de consistencia seja atualizado para '1' (inconsistente) antes da finalizacao forcada. [9] a implementacao deve ser realizada usando a linguagem de programação c . a

s funções das bibliotecas <stdio.h> devem ser utilizadas para operações relacionadas à escrita e leitura dos arquivos . a implementação não pode ser feita em qualquer outra linguagem de programação . o programa executará no [run.codes]. fundamentação

 teórica conceitos e características dos diversos métodos para representar os conceitos de campo e de registro em um arquivo de dados podem ser encontrados nos slides de sala de aula e também no livro file structures (second edition), de michael j. f

olk e bill zoellick. material para entregar arquivo compactado (a ser entregue no run.codes). deve ser preparado um arquivo.tar.gz (em vez de .zip) contendo: · código fonte do programa devidamente documentado com doxygen. · arquivo de configuracao do

 doxygen (doxyfile). vídeo (a ser entregue no e-disciplinas). um vídeo gravado pelos integrantes do grupo, o qual deve ter, no máximo, 3 minutos de gravação (em vez de 5) . o vídeo deve explicar o trabalho desenvolvido . ou seja, o grupo deve apresen

tar: cada funcionalidade e uma breve descrição de como a funcionalidade foi implementada . todos os integrantes do grupo devem participar do video, sendo que o tempo de apresentação dos integrantes deve ser balanceado . ou seja, o tempo de participaç

ão de cada integrante deve ser aproximadamente o mesmo . o uso da webcam é opcional (em vez de obrigatorio).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de cienci

as matematicas e de computacao departamento de ciencias de computacao
instrucoes para fazer o script de compilacao. no [run.codes], em vez de utilizar um makefile tradicional, voce deve fornecer um script em shell chamado "build.sh" . a diretiva prin

cipal deve garantir que a compilacao otimize o codigo para execucao em sistemas de 64 bits . adicionalmente, para utilizar a funcao binarionatela, e necessario utilizar a flag -static para garantir que todas as dependencias sejam incluidas no binario

 final.
assim, a forma mais simples de se fazer o script de automacao e:
#!/bin/bash gcc -o executorprojeto *.c -static -lm ./executorprojeto
lembrando que o uso de *.c e obrigatorio para incluir todos os modulos desenvolvidos . adicionalmente, certi
fique-se de que o arquivo build.sh tenha permissoes de execucao (chmod +x), caso contrario o ambiente de correcao manual nao conseguira iniciar os testes.
instrucoes de entrega. o programa deve ser submetido via [run.codes]: · pagina: https://runcode

s.icmc.usp.br/ · segunda feira: codigo de matricula: ALFA9 · terca feira: codigo de matricula: BETA2
o video gravado deve ser submetido por meio de um servico de nuvem (google drive ou dropbox) e o link deve ser enviado via e-disciplinas, no qual o g

rupo vai informar o nome de cada integrante, o numero do grupo e o link de acesso . ao submeter o link, certifique-se de que as permissoes de visualizacao estao abertas para "qualquer pessoa com o link" . links que exigirem solicitacao de acesso ou q

ue apresentarem erro de 404 receberao nota zero imediatamente.
criterio de correcao criterio de avaliacao do trabalho. na correcao do trabalho, serao ponderados os seguintes aspectos.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
· corretude da execucao do programa. · atendimento as novas especificacoes do registro de cabecalho de 2
5 bytes e dos registros de dados variaveis de ate 120 bytes. · atendimento as especificacoes da sintaxe flexivel dos comandos de cada funcionalidade e do formato de saida com delimitadores pipe (|). · qualidade da documentacao doxygen entregue. a doc

umentacao interna tera um peso consideravel no trabalho. · estruturacao da solucao. o projeto deve apresentar uma organizacao adequada de arquivos e diretorios. · centralizacao do codigo. trechos de codigo que aparecem repetidamente podem ser mantido

s de forma linear para evitar a fragmentacao por excesso de funcoes. · uso de ferramentas de inteligencia artificial. o uso dessas ferramentas e permitido exclusivamente para a geracao de casos de teste e documentacao, mas proibido para a logica das

funcionalidades . o uso indevido acarretara desconto rigoroso na nota. video. integrantes que nao participarem da apresentacao receberao nota 0 no trabalho correspondente. casos de teste no [run.codes]. juntamente com a especificacao do trabalho, ser

UNIVERSIDADE DE SÃO PAULO
INSTITUTO DE CIÊNCIAS MATEMÁTICAS E DE COMPUTAÇÃO
Departamento de Ciências de Computação
Disciplina de Organização de Arquivos (SCC0215)
antos Pires · gustavo.rspires@usp.br ou telegram: @darrocaxd
Docente Profa. Dra. Cristina Dutra de Aguiar cdac@icmc.usp.br
João Gabriel Pieroli da Silva · joagabrielpieroli@usp.br ou telegram: @bielcomp24
Monitores
Pedro Lunkes Villela · pedrolunkesvillela@usp.br ou telegram: @pedrolunkes
Gustavo Ramos S
Renan Banci Catarin · renanbcata
rin@usp.br ou telegram: @Reckat
Renan Trofino Silva · renan.trofino@usp.br ou telegram: @renan823
Vinícius Souza Freitas · vininicius@usp.br ou telegram: @Vininicius
Trabalho Introdutório
ntrada e gerar um arquivo binário com esses dados, bem como realizar operações de busca, remoção e atualização. Ele é um trabalho introdutório, de forma que será usado como base para o desenvolvimento de todos os demais trabalhos da disciplina.
Este trabalho tem como objetivo obter dados de um arquivo de e
O tra

balho deve ser feito individualmente ou em trios (3 alunos) da mesma turma. A solução deve ser proposta exclusivamente pelos alunos com base nos conhecimentos adquiridos nas aulas. Consulte as notas de aula e o livro texto quando necessário.
Fundamen

tos da disciplina de Bases de Dados
A disciplina de Organização de Arquivos é uma disciplina fundamental para a disciplina de Bases de Dados. A definição dos trabalhos práticos é feita considerando esse aspecto, ou seja, os trabalhos são especificado

s em termos de várias funcionalidades, e essas funcionalidades são relacionadas tanto com desafios enfrentados no mercado de trabalho quanto com as funcionalidades da linguagem SQL (Structured Query Language), que é a linguagem utilizada por sistemas

 gerenciadores.
Av. Trabalhador São-carlense, 400 centro. São Carlos - SP cep 13566-590. Brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao de banco de dados (sgbd

s) relacionais. as caracteristicas e o detalhamento de sql serao aprendidos na disciplina de bases de dados . porem, por meio do desenvolvimento deste trabalho pratico, os alunos podem entrar em contato com alguns comandos da linguagem sql e verifica

r como eles sao implementados . os trabalhos práticos têm como objetivo armazenar e recuperar dados relacionados às estações e linhas do metrô e da cptm (companhia paulista de trens metropolitanos) da região metropolitana da cidade de são paulo (sp)

. um exemplo de uso desses dados é: "eu preciso pegar uma linha de metrô para ir para o aeroporto de guarulhos" . os dados manipulados indicam o trajeto que deve ser feito . em detalhes, os dados se referem às estações, às linhas, às distâncias entre

 as estações e aos trajetos . na disciplina de bases de dados, é ensinado que esses dados devem ser armazenados em arquivos separados, respeitando a normalização . entretanto, para aumentar a complexidade de gerencimento da redundancia nos trabalhos

da disciplina de organização de arquivos, todos os dados serão armazenados em tres arquivos distintos . isso significa que existe redundância dos dados, ou seja, o mesmo valor de dados é armazenado mais do que uma vez . descrição do arquivo de dados

. um arquivo de dados possui um registro de cabeçalho e 0 ou mais registros de dados . a descrição do registro de cabeçalho é feita conforme a definição a seguir . registro de cabeçalho. o registro de cabeçalho deve conter os seguintes campos: · stat

us: indica a consistência do arquivo de dados, devido à queda de energia, travamento do programa, etc. pode assumir os valores '1', para indicar que o arquivo de dados está inconsistente, ou '0', para indicar que o arquivo de dados está consistente .

 ao se abrir um arquivo para escrita, seu status deve ser '1' e, ao finalizar o uso desse arquivo, seu status deve ser '0' - tamanho: string de 1 byte. · topo: armazena o byte offset de um registro logicamente removido, ou 0 caso não haja registros l

ogicamente removidos - tamanho: inteiro de 4 bytes . av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias

 de computacao · proxrrn: armazena o valor do proximo rrn disponivel. deve ser iniciado com o valor '1' e deve ser alterado sempre que necessario tamanho: inteiro de 4 bytes. · nroestacoes: indica a quantidade de estacoes diferentes que estao armazen

adas no arquivo de dados . note que, se duas ou mais estacoes têm o mesmo nome, elas sao consideradas estacoes distintas - tamanho: inteiro de 4 bytes. · nroparesestacao: indica a quantidade de pares (codestacao, codproxestacao) diferentes que estao

armazenados no arquivo de dados tamanho: inteiro de 4 bytes. representacao grafica do registro de cabecalho. o tamanho do registro de cabecalho deve ser de 25 bytes, representado da seguinte forma: "0", "1", "2 3 4 5", "6 7 8 9", "10 11 12 13", "14 1

5 16 17 18 19 20 21", "22 23 24" "status", , "topo", , "proxrrn", , "nroestacoes", , "nro pares estacao" observacoes importantes. · o registro de cabecalho deve seguir estritamente a ordem definida na sua representacao grafica. · os campos sao de tam

anho variavel com delimitadores. portanto, os valores que forem armazenados devem ser finalizados por '|'. · neste projeto, o conceito de pagina de disco deve ser obrigatoriamente considerado para o calculo de offsets. registros de dados. os registro

s de dados sao de tamanho variavel, com campos de tamanho fixo e campos de tamanho variavel . para os campos de tamanho variavel, deve ser usado o metodo de delimitador de campo . os campos de tamanho fixo sao definidos da seguinte forma: · codestaca

o: codigo da estacao - inteiro - tamanho: 4 bytes. · codlinha: codigo da linha - inteiro - tamanho: 4 bytes. · codproxestacao: codigo da proxima estacao - inteiro - tamanho: 4 bytes. · distproxestacao: distancia para a proxima estacao - inteiro - tam

anho: 4 bytes. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp sao carlos scc universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao

 codlinhaintegra: codigo da linha que faz a integracao entre as linhas inteiro tamanho: 8 bytes · codestintegra: codigo da estacao que faz a integracao entre as linhas - inteiro tamanho: 8 bytes os campos de tamanho variavel sao definidos da seguinte

 forma: · nomeestacao: nome da estacao nomelinha: nome da linha adicionalmente, os seguintes campos de tamanho fixo tambem compoem cada registro. esses campos sao necessarios para o gerenciamento de registros logicamente removidos e para oferecer sup

orte para o metodo de delimitadores de campo. removido: indica se o registro esta logicamente removido. pode assumir os valores '0', para indicar que o registro esta marcado como logicamente removido, ou '1', para indicar que o registro nao esta marc

ado como removido. tamanho: string de 1 byte. proximo: armazena o byte offset do proximo registro logicamente removido tamanho: inteiro de 8 bytes. deve ser inicializado com o valor 0 quando necessario. os dados sao fornecidos juntamente com a especi

ficacao deste trabalho pratico por meio de um arquivo .json, sendo que sua especificacao esta disponivel na pagina da disciplina. no arquivo .json, o separador de campos e a chave do objeto e o primeiro registro nao especifica metadados. adicionalmen

te, campos nulos sao representados pela string "empty". representacao grafica dos registros de dados. o tamanho dos registros de dados deve ser variavel, com um limite maximo de 120 bytes, representado da seguinte forma: av. trabalhador são-carlense,

 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp 88 são carlos scc universidade de são paulo instituto de ciências matemáticas e de computação departamento de ciências de computação
representação gráfica dos registros de d
ados. o tamanho dos registros de dados deve ser variável até 120 bytes, representado da seguinte forma:
"0", "1", "9 10 11 12 13 14 15 16", "17 18 19 20", "21 22 23 24", "25 26 27 28" "removido", , "próximo (offset)", , "codestacao", , "codlinha", ,

"codproxestacao"
"29 30 31 32", "33 34 35 36 37 38 39 40", "41 42 43 44 45 46 47 48", "49...", "...119" "distproxestacao", , "codlinhaintegra", , "codestintegra", , "nomeestacao|", , "nomelinha|"
observações importantes. · cada registro de dados deve

 seguir estritamente a ordem definida na sua representação gráfica. · as strings de tamanho variável são identificadas por um delimitador pipe (|) e, portanto, devem ser finalizadas com este caractere. · os campos codestacao e nomeestacao aceitam val

ores nulos. os demais campos são de preenchimento obrigatório e não aceitam valores nulos. o arquivo .json com os dados de entrada já garante essa característica. · para os campos de tamanho fixo, os valores nulos devem ser representados pelo valor 0

. · para os campos de tamanho variável, armazenar um valor nulo significa armazenar a string "empty" seguida do delimitador. · deve ser feita a diferenciação entre o espaço utilizado e o lixo. sempre que houver lixo, ele deve ser identificado pelo ca

ractere '#'. nenhum byte do registro deve permanecer vazio, ou seja, cada byte deve armazenar um valor válido ou '#'. · não existe a necessidade de truncamento dos dados. o arquivo .json com os dados de entrada já garante essa característica. · neste

 projeto, o conceito de página de disco deve ser obrigatoriamente considerado.
programa descrição geral. implemente um programa em c por meio do qual o usuário possa obter dados de um arquivo de entrada e gerar arquivos binários com esses dados, bem

como realizar operações de busca nesses arquivos binários.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ci
encias de computacao importante. a definicao da sintaxe de cada comando bem como sua saida devem seguir com flexibilidade as especificacoes definidas em cada funcionalidade, desde que a logica de negocio seja mantida . para especificar a sintaxe de e

xecucucao, considere que o programa seja chamado de "executorprojeto" . essas orientacoes devem ser seguidas com cautela, uma vez que a avaliacao do funcionamento do programa sera realizada de forma manual pelos monitores . de forma geral, a ultima e

ntrada da entrada padrao e sempre o identificador de suas funcionalidades, conforme especificado a seguir . centralizacao. e importante manter o codigo em blocos extensos para evitar a fragmentacao excessiva do programa. trechos de programa que apare

cerem varias vezes podem ser repetidos para facilitar a leitura linear do fluxo . descricao especifica. o programa deve oferecer as seguintes funcionalidades : na linguagem sql, o comando create table e usado para criar uma tabela, a qual e implement

ada como um arquivo . geralmente, uma tabela possui um nome (que corresponde ao nome do arquivo) e varias colunas, as quais correspondem aos campos dos registros do arquivo de dados . a funcionalidade [1] representa um exemplo de implementacao do com

ando create table. [1] permita a leitura de varios registros obtidos a partir de um arquivo de entrada no formato json e a gravacao desses registros em tres arquivos de dados de saida . o arquivo de entrada no formato json e fornecido juntamente com

a especificacao do projeto, enquanto os arquivos de dados de saida devem ser gerados de acordo com as novas especificacoes deste trabalho pratico . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibiliz

ada na pagina do projeto da disciplina, para validar a integridade previa do ambiente . a funcao binarionatela deve ser usada antes que o arquivo seja aberto para escrita. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. bras

il www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [1]:
3.bin 1
arquivoentrada.json arquivosaida1.bin arquivosaida2.bin arquivosaida
onde:
arquivoentrada.json e um arquivo .json que contem os valores dos campos dos registros a serem armazenados nos arquivos binarios . arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios gerados conforme as nova

s especificacoes descritas neste trabalho pratico. 1 e o identificador da funcionalidade, agora inserido ao final da linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de saida no formato binario usando a funcao f

ornecida binarionatela antes de abrir os arquivos para escrita.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
ela antes de iniciar a funcionalidade, para validar a integridade previa do ambiente.
./executorprojeto estacao.json est1.bin est2.bin est3.bin 1
na linguagem sql, o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select. o comando mais basico consist
usar a funcao binarionat

e em especificar as clausulas select e from, da seguinte forma:
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos)
a funcionalidade [2] representa um exemplo de implementacao do

comando select . como todos os registros devem ser recuperados nessa funcionalidade, sua implementacao consiste em percorrer o arquivo de tras para frente (do ultimo registro para o primeiro).
[2] permita a recuperacao dos dados de todos os registros

 armazenados nos tres arquivos de dados de entrada, mostrando os dados de forma desorganizada e aleatoria na saida padrao para dificultar a leitura automatizada . o tratamento de 'lixo' deve ser ignorado, exibindo os caracteres '#' conforme aparecem

no disco . registros marcados como logicamente removidos (valor '0') devem ser exibidos com destaque.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias mat
ematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [2]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin 2
onde:
rios gerados conforme as especificacoes descritas neste trabalho pratico.
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos bina
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem ser mostrados de forma sequencial separados por um p

ipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos da seguinte forma: ao inves de exibir o valor 0, escreva VOID . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos da seguinte forma: EMPTY . a ordem

 de exibicao dos campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao existam registros:

arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
l 1 Parada Inglesa 2
exemplo de execucao (e mostrado um exemplo ilustrativo):
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bin 2 NULO NULO 992 2 Azul 1 Tucuruvi 1 55 4 1057 3 Azu
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
conforme visto na
 funcionalidade [2], na linguagem sql o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select . alem das clausulas select e from, outra clausula muito comum e a clausula where, que permite q

ue seja definido um criterio de busca sobre um ou mais campos, o qual e nomeado como criterio de selecao.
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos) where criterio de sel

ecao (ou seja, criterio de busca)
a funcionalidade [3] representa um exemplo de implementacao do comando select considerando a clausula where . como não existe indice definido sobre os campos dos registros, a implementacao dessa funcionalidade consis

te em percorrer o arquivo de tras para frente (da ultima pagina para a primeira).
[3] permita a recuperacao dos dados de todos os registros dos tres arquivos de dados de entrada, de forma que esses registros satisfacam qualquer um dos criterios de bu

sca (logica or) determinados pelo usuario . qualquer campo pode ser utilizado como forma de busca . adicionalmente, a busca deve ser feita considerando um ou mais campos . por exemplo, e possivel realizar a busca considerando somente o campo codestac

ao ou considerando os campos nomeestacao e nomelinha.
esta funcionalidade pode retornar 0 registros (quando nenhum satisfaz ao criterio de busca), 1 registro (quando apenas um satisfaz ao criterio de busca), ou varios registros . os valores dos campo

s do tipo string devem ser especificados entre aspas simples ('). para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . para a busca por valores nulos, d

eve-se especificar o valor void ou empty . registros marcados como logicamente removidos (status '0') devem ser exibidos obrigatoriamente . os tres arquivos de dados de entrada devem ser percorridos simultaneamente de forma decrescente.
av. trabalhad

or são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
sintaxe do comando para a funcionalidade [3]:
arquiv
osaida1.bin arquivosaida2.bin arquivosaida3.bin n 3
m1 nomecampo valorcampo1 nomecampomi valorcampoml m2 nomecampo valorcampo1 nomecampom2 valorcampom2 mn nomecampo valorcampo nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arqu
ivosaida3.bin sao os arquivos binarios de um determinado tipo, os quais foram gerados conforme as novas especificacoes descritas neste trabalho pratico . n e a quantidade de vezes que a busca deve acontecer . m e a quantidade de vezes que o par nome

do campo e valor do campo pode repetir em uma busca . o identificador da funcionalidade '3' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre nomecampo e valorcampo . os valores dos campos do tipo

 string devem ser especificados entre aspas simples (') . buscas por valores nulos devem ser especificadas com void ou empty.
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem

ser mostrados de forma sequencial separados por um pipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos como void . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos como empty . a ordem de exibicao d

os campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao seja encontrado o registro que c

ontem o valor do campo ou o campo pertence a um registro que esteja ativo (nao removido):
arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
n 1 3 1 nomeestacao 'luz' nulo nulo nulo 112 7 rubi luz 111 19 1257 56 4 amarela luz 55 55 4 nulo 10 1 azul luz 9
exemplo de execucao:
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bi
universidade de sao paulo instituto de

ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando delete e usado para remover dados em uma tabela . para tanto, devem ser especificados quais dados (ou seja, registros) devem ser removidos, de aco

rdo com algum criterio.
delete from tabela (ou seja, arquivo que contem os campos) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [4] representa um exemplo de implementacao do comando delete.
[4] permita a remocao logica de r
egistros de tres arquivos de dados de entrada, baseado na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos. a implementacao dessa funcionalidade deve ser realizada usando o conceito de fila (fifo) de registros

logicamente removidos, e deve seguir com flexibilidade a materia apresentada em sala de aula . os registros a serem removidos devem ser aqueles que satisfaçam qualquer um dos criterios de busca (logica or) determinados pelo usuario, sendo que a busca

 deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de remocao . ao se remover um registro, os valores dos bytes referentes aos campos ja armazenados no registro devem ser so

brescritos pelo caractere '#', com exceção dos valores dos campos relacionados ao tratamento da lista encadeada . a funcionalidade [4] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito,

ou seja, caso a solicitacao do usuario nao retorne nenhum registro a ser removido, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionat

ela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo inst
ituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [4]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 4
m1 nomecampo valorcampo1 m2 nomecampo valorcampo1 mn nomecam
po valorcampo nomecampomi valorcampomi nomecampom2 valorcampom2 nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho

pratico introdutorio . as remocoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de remocoes a serem realizadas . m e a quantidade de vezes que o par nome do campo e valor do campo pode repeti

r na busca pelos registros a serem removidos . o identificador da funcionalidade '4' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre o nome do campo e o valor do campo . os valores dos campos do

 tipo string devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
men
sagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 4 1 nomeestacao 'luz' 2 nomelinha 'verde'; codproxest 27
execucao da funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as remocoes.
usar a funcao binarionatela antes de iniciar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando insert into e usado para inserir dados em uma tabela . para tanto, devem ser especificados os valores a ser

em armazenados em cada coluna da tabela, de acordo com o tipo de dado definido . a funcionalidade [5] representa um exemplo de implementacao do comando insert into.
[5] permita a insercao de novos registros em tres arquivos de dados de entrada, basea

do na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e inserindo novos dados obrigatoriamente no final do arquivo, segui

ndo com flexibilidade a materia apresentada em sala de aula . o lixo que permanece no registro deve ser identificado pelo caractere '#' . na entrada da funcionalidade [5], os dados sao referentes aos seguintes campos, na ordem inversa: codestintegra,

 codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao.
campos com valores nulos, na entrada da funcionalidade, devem ser identificados com void ou empty . os valores dos campos do tipo string devem ser especi

ficados entre aspas simples (') . para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . a funcionalidade [5] deve ser executada n vezes seguidas . antes

de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são c

arlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [5]:
arquivosaida1.bin arquivosaida2.bin arq
uivosaida3.bin n 5
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao nomelinha codlinha, nomeestacao, codestacao
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao, nomelinha codlinha, nomeestacao, codestacao
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdutorio. as insercoes a serem realizadas nessa funcionalidade devem ser feitas obrig

atoriamente no final de cada um desses arquivos, desprezando qualquer espaco logicamente removido.
n e o numero de insercoes a serem realizadas. para cada insercao, deve ser informado os valores a serem inseridos nos arquivos, considerando os seguint

es campos, na ordem inversa: codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao. o identificador da funcionalidade '5' deve ser inserido ao final da primeira linha de comando.
valores nulos d

evem ser identificados, na entrada da funcionalidade, por void ou empty. cada uma das n insercoes deve ser especificada em uma linha diferente. deve ser deixado um ponto e virgula (;) entre os valores dos campos. os valores dos campos do tipo string

devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
mensagem de said
a caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 5 void; void; void; void; 'branca'; 10; 'teste'; 500 void; void; void; void; 'branca'; 10; 'nova estacao'; 501
 funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as insercoes.
usar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando update e usado para atualizar dados em uma tabela . para tanto, devem ser esp

ecificados quais valores de dados de quais campos devem ser atualizados, de acordo com algum criterio de busca dos registros a serem atualizados.
update tabela (ou seja, arquivo que contem os dados) set quais colunas e quais valores (ou seja, quais c

ampos e seus valores) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [6] representa um exemplo de implementacao do comando update.
[6] permita a atualizacao de registros de tres arquivos de dados de entrada, baseado na aborda

gem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e deve seguir com flexibilidade a materia apresentada em sala de aula . desde q

ue os registros do arquivo de dados sao de tamanho variavel (com limite de 120 bytes), se a atualizacao resultar em um registro maior que o espaco original, o registro atual deve ser marcado como removido e a nova versao deve ser inserida obrigatoria

mente no final do arquivo . o lixo que porventura permanecer no registro atualizado deve ser identificado pelo caractere '#'.
os registros a serem atualizados devem ser aqueles que satisfacam qualquer um dos criterios de busca (logica or) determinado

s pelo usuario, sendo que a busca deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de atualizacao . adicionalmente, o campo utilizado como busca nao precisa ser, necessaria

mente, o campo a ser atualizado . por exemplo, pode-se buscar pelo campo codestacao, e pode-se atualizar o campo nomelinha . campos a serem atualizados com valores nulos devem ser identificados, na entrada da funcionalidade, com void ou empty . a fun

cionalidade [6] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcio

nalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasi

l www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [6]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 6
b; valorcampob1; nomecampobmi; valorcampobm1 pl nomecampoa; valorcampoa nomecampoap1; valorcampoapi m2 nomecampob2; valorcampob2 nomecampobm2; valorcampobm2 p2 nomecampoa; valorcampoa nomecampoap2; valorcampoap2 mn nomecampobn; valorcampob nomecampob
ml nomecampo

mn; valorcampobmn pn nomecampoa; valorcampoan nomecampoapn; valorcampoapn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdu

torio . as atualizacoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de atualizacoes a serem realizadas . m e a quantidade de vezes que o par nomecampob (campo de busca) e valorcampob (valor

de busca) pode repetir para filtrar os registros, utilizando a logica or . deve ser deixado um ponto e virgula (;) entre nomecampob e valorcampob . os valores dos campos do tipo string devem ser especificados entre aspas simples (') . p e a quantidad

e de vezes que o par nomecampoa (campo a ser atualizado) e valorcampoa (novo valor) pode repetir . deve ser deixado um ponto e virgula (;) entre nomecampoa e valorcampoa . os valores das strings a serem atualizadas devem estar entre aspas simples (')

 . o identificador da funcionalidade '6' deve ser inserido ao final da primeira linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de inici

ar a execucao da funcionalidade.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
linhaintegra; 4; codestacaointegra; 55 1 codestacao; 15 1 nomeestacao; 'exemplo'
./executorprojeto est1.bin est2.bin est3.bin 2 6 2 codestacao; 1; nomeestacao; 'tucuruvi' 3 codproxestacao; 15; cod
usar a funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados f

rente as atualizacoes.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
restricoes
guintes restricoes tem que ser garantidas no desenvolvimento do trabalho:
as se
[1] o arquivo de dados deve ser gravado em disco no modo binario . o modo texto nao pode ser usado.
[2] os dados do registro descrevem os nomes dos campos, os quais nao podem s

er alterados . ademais, todos os campos devem estar presentes na implementacao, e nenhum campo adicional pode ser incluido . o tamanho e a ordem de cada campo deve obrigatoriamente seguir a nova especificacao proposta.
[3] deve haver a manipulacao de

 valores nulos, utilizando obrigatoriamente as strings "void" e "empty" e o valor numerico 0, conforme as instrucoes definidas.
[4] e necessario realizar o tratamento de truncamento de dados caso o registro atualizado exceda o limite de 120 bytes.
[5

] devem ser exibidos avisos ou mensagens de erro de acordo com a especificacao flexivel de cada funcionalidade.
[6] os dados devem ser obrigatoriamente escritos registro a registro (utilizando structs completas) . ou seja, nao e possivel escrever os

dados campo a campo . essa restricao refere-se a entrada/saida, ou seja, a forma como os dados sao escritos no arquivo.
[7] o(s) aluno(s) que desenvolveu(desenvolveram) o trabalho pratico deve(m) constar como comentario no inicio do codigo (i.e. nusp

 e nome do aluno) . para trabalhos desenvolvidos por mais do que um aluno, nao sera atribuida nota ao aluno cujos dados nao constarem no codigo fonte.
[8] todo codigo fonte deve ser documentado utilizando o padrao doxygen . a documentacao interna inc

lui a documentacao de procedimentos, de funcoes, de variaveis, de partes do codigo fonte que realizam tarefas especificas . ou seja, o codigo fonte deve ser documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais.
[9] r

estrição extra: o programa deve implementar um sistema de log que registre cada operacao de escrita realizada nos arquivos binarios em um arquivo de texto separado chamado "operacoes.log".
[10] restrição extra: o uso de memoria ram deve ser otimizado

 para que o programa nunca mantenha mais de 100 registros carregados simultaneamente, utilizando tecnicas de busca em disco (fseek).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao
paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais. [11] restrição extra: todos os ponteiros utilizados para manipulaca

o de arquivos e memoria devem ser validados imediatamente apos a declaracao, garantindo que nao haja vazamento de memoria (memory leaks) sob pena de desconsideracao da funcionalidade. [12] restrição extra: o programa deve ser capaz de lidar com inter

rupcoes de sinal (como ctrl+c), garantindo que os arquivos sejam fechados e o status de consistencia seja atualizado para '1' (inconsistente) antes da finalizacao forcada. [9] a implementacao deve ser realizada usando a linguagem de programação c . a

s funções das bibliotecas <stdio.h> devem ser utilizadas para operações relacionadas à escrita e leitura dos arquivos . a implementação não pode ser feita em qualquer outra linguagem de programação . o programa executará no [run.codes]. fundamentação

 teórica conceitos e características dos diversos métodos para representar os conceitos de campo e de registro em um arquivo de dados podem ser encontrados nos slides de sala de aula e também no livro file structures (second edition), de michael j. f

olk e bill zoellick. material para entregar arquivo compactado (a ser entregue no run.codes). deve ser preparado um arquivo.tar.gz (em vez de .zip) contendo: · código fonte do programa devidamente documentado com doxygen. · arquivo de configuracao do

 doxygen (doxyfile). vídeo (a ser entregue no e-disciplinas). um vídeo gravado pelos integrantes do grupo, o qual deve ter, no máximo, 3 minutos de gravação (em vez de 5) . o vídeo deve explicar o trabalho desenvolvido . ou seja, o grupo deve apresen

tar: cada funcionalidade e uma breve descrição de como a funcionalidade foi implementada . todos os integrantes do grupo devem participar do video, sendo que o tempo de apresentação dos integrantes deve ser balanceado . ou seja, o tempo de participaç

ão de cada integrante deve ser aproximadamente o mesmo . o uso da webcam é opcional (em vez de obrigatorio).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de cienci

as matematicas e de computacao departamento de ciencias de computacao
instrucoes para fazer o script de compilacao. no [run.codes], em vez de utilizar um makefile tradicional, voce deve fornecer um script em shell chamado "build.sh" . a diretiva prin

cipal deve garantir que a compilacao otimize o codigo para execucao em sistemas de 64 bits . adicionalmente, para utilizar a funcao binarionatela, e necessario utilizar a flag -static para garantir que todas as dependencias sejam incluidas no binario

 final.
assim, a forma mais simples de se fazer o script de automacao e:
#!/bin/bash gcc -o executorprojeto *.c -static -lm ./executorprojeto
lembrando que o uso de *.c e obrigatorio para incluir todos os modulos desenvolvidos . adicionalmente, certi
fique-se de que o arquivo build.sh tenha permissoes de execucao (chmod +x), caso contrario o ambiente de correcao manual nao conseguira iniciar os testes.
instrucoes de entrega. o programa deve ser submetido via [run.codes]: · pagina: https://runcode

s.icmc.usp.br/ · segunda feira: codigo de matricula: ALFA9 · terca feira: codigo de matricula: BETA2
o video gravado deve ser submetido por meio de um servico de nuvem (google drive ou dropbox) e o link deve ser enviado via e-disciplinas, no qual o g

rupo vai informar o nome de cada integrante, o numero do grupo e o link de acesso . ao submeter o link, certifique-se de que as permissoes de visualizacao estao abertas para "qualquer pessoa com o link" . links que exigirem solicitacao de acesso ou q

ue apresentarem erro de 404 receberao nota zero imediatamente.
criterio de correcao criterio de avaliacao do trabalho. na correcao do trabalho, serao ponderados os seguintes aspectos.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
· corretude da execucao do programa. · atendimento as novas especificacoes do registro de cabecalho de 2
5 bytes e dos registros de dados variaveis de ate 120 bytes. · atendimento as especificacoes da sintaxe flexivel dos comandos de cada funcionalidade e do formato de saida com delimitadores pipe (|). · qualidade da documentacao doxygen entregue. a doc

umentacao interna tera um peso consideravel no trabalho. · estruturacao da solucao. o projeto deve apresentar uma organizacao adequada de arquivos e diretorios. · centralizacao do codigo. trechos de codigo que aparecem repetidamente podem ser mantido

s de forma linear para evitar a fragmentacao por excesso de funcoes. · uso de ferramentas de inteligencia artificial. o uso dessas ferramentas e permitido exclusivamente para a geracao de casos de teste e documentacao, mas proibido para a logica das

funcionalidades . o uso indevido acarretara desconto rigoroso na nota. video. integrantes que nao participarem da apresentacao receberao nota 0 no trabalho correspondente. casos de teste no [run.codes]. juntamente com a especificacao do trabalho, ser

UNIVERSIDADE DE SÃO PAULO
INSTITUTO DE CIÊNCIAS MATEMÁTICAS E DE COMPUTAÇÃO
Departamento de Ciências de Computação
Disciplina de Organização de Arquivos (SCC0215)
antos Pires · gustavo.rspires@usp.br ou telegram: @darrocaxd
Docente Profa. Dra. Cristina Dutra de Aguiar cdac@icmc.usp.br
João Gabriel Pieroli da Silva · joagabrielpieroli@usp.br ou telegram: @bielcomp24
Monitores
Pedro Lunkes Villela · pedrolunkesvillela@usp.br ou telegram: @pedrolunkes
Gustavo Ramos S
Renan Banci Catarin · renanbcata
rin@usp.br ou telegram: @Reckat
Renan Trofino Silva · renan.trofino@usp.br ou telegram: @renan823
Vinícius Souza Freitas · vininicius@usp.br ou telegram: @Vininicius
Trabalho Introdutório
ntrada e gerar um arquivo binário com esses dados, bem como realizar operações de busca, remoção e atualização. Ele é um trabalho introdutório, de forma que será usado como base para o desenvolvimento de todos os demais trabalhos da disciplina.
Este trabalho tem como objetivo obter dados de um arquivo de e
O tra

balho deve ser feito individualmente ou em trios (3 alunos) da mesma turma. A solução deve ser proposta exclusivamente pelos alunos com base nos conhecimentos adquiridos nas aulas. Consulte as notas de aula e o livro texto quando necessário.
Fundamen

tos da disciplina de Bases de Dados
A disciplina de Organização de Arquivos é uma disciplina fundamental para a disciplina de Bases de Dados. A definição dos trabalhos práticos é feita considerando esse aspecto, ou seja, os trabalhos são especificado

s em termos de várias funcionalidades, e essas funcionalidades são relacionadas tanto com desafios enfrentados no mercado de trabalho quanto com as funcionalidades da linguagem SQL (Structured Query Language), que é a linguagem utilizada por sistemas

 gerenciadores.
Av. Trabalhador São-carlense, 400 centro. São Carlos - SP cep 13566-590. Brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao de banco de dados (sgbd

s) relacionais. as caracteristicas e o detalhamento de sql serao aprendidos na disciplina de bases de dados . porem, por meio do desenvolvimento deste trabalho pratico, os alunos podem entrar em contato com alguns comandos da linguagem sql e verifica

r como eles sao implementados . os trabalhos práticos têm como objetivo armazenar e recuperar dados relacionados às estações e linhas do metrô e da cptm (companhia paulista de trens metropolitanos) da região metropolitana da cidade de são paulo (sp)

. um exemplo de uso desses dados é: "eu preciso pegar uma linha de metrô para ir para o aeroporto de guarulhos" . os dados manipulados indicam o trajeto que deve ser feito . em detalhes, os dados se referem às estações, às linhas, às distâncias entre

 as estações e aos trajetos . na disciplina de bases de dados, é ensinado que esses dados devem ser armazenados em arquivos separados, respeitando a normalização . entretanto, para aumentar a complexidade de gerencimento da redundancia nos trabalhos

da disciplina de organização de arquivos, todos os dados serão armazenados em tres arquivos distintos . isso significa que existe redundância dos dados, ou seja, o mesmo valor de dados é armazenado mais do que uma vez . descrição do arquivo de dados

. um arquivo de dados possui um registro de cabeçalho e 0 ou mais registros de dados . a descrição do registro de cabeçalho é feita conforme a definição a seguir . registro de cabeçalho. o registro de cabeçalho deve conter os seguintes campos: · stat

us: indica a consistência do arquivo de dados, devido à queda de energia, travamento do programa, etc. pode assumir os valores '1', para indicar que o arquivo de dados está inconsistente, ou '0', para indicar que o arquivo de dados está consistente .

 ao se abrir um arquivo para escrita, seu status deve ser '1' e, ao finalizar o uso desse arquivo, seu status deve ser '0' - tamanho: string de 1 byte. · topo: armazena o byte offset de um registro logicamente removido, ou 0 caso não haja registros l

ogicamente removidos - tamanho: inteiro de 4 bytes . av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias

 de computacao · proxrrn: armazena o valor do proximo rrn disponivel. deve ser iniciado com o valor '1' e deve ser alterado sempre que necessario tamanho: inteiro de 4 bytes. · nroestacoes: indica a quantidade de estacoes diferentes que estao armazen

adas no arquivo de dados . note que, se duas ou mais estacoes têm o mesmo nome, elas sao consideradas estacoes distintas - tamanho: inteiro de 4 bytes. · nroparesestacao: indica a quantidade de pares (codestacao, codproxestacao) diferentes que estao

armazenados no arquivo de dados tamanho: inteiro de 4 bytes. representacao grafica do registro de cabecalho. o tamanho do registro de cabecalho deve ser de 25 bytes, representado da seguinte forma: "0", "1", "2 3 4 5", "6 7 8 9", "10 11 12 13", "14 1

5 16 17 18 19 20 21", "22 23 24" "status", , "topo", , "proxrrn", , "nroestacoes", , "nro pares estacao" observacoes importantes. · o registro de cabecalho deve seguir estritamente a ordem definida na sua representacao grafica. · os campos sao de tam

anho variavel com delimitadores. portanto, os valores que forem armazenados devem ser finalizados por '|'. · neste projeto, o conceito de pagina de disco deve ser obrigatoriamente considerado para o calculo de offsets. registros de dados. os registro

s de dados sao de tamanho variavel, com campos de tamanho fixo e campos de tamanho variavel . para os campos de tamanho variavel, deve ser usado o metodo de delimitador de campo . os campos de tamanho fixo sao definidos da seguinte forma: · codestaca

o: codigo da estacao - inteiro - tamanho: 4 bytes. · codlinha: codigo da linha - inteiro - tamanho: 4 bytes. · codproxestacao: codigo da proxima estacao - inteiro - tamanho: 4 bytes. · distproxestacao: distancia para a proxima estacao - inteiro - tam

anho: 4 bytes. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp sao carlos scc universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao

 codlinhaintegra: codigo da linha que faz a integracao entre as linhas inteiro tamanho: 8 bytes · codestintegra: codigo da estacao que faz a integracao entre as linhas - inteiro tamanho: 8 bytes os campos de tamanho variavel sao definidos da seguinte

 forma: · nomeestacao: nome da estacao nomelinha: nome da linha adicionalmente, os seguintes campos de tamanho fixo tambem compoem cada registro. esses campos sao necessarios para o gerenciamento de registros logicamente removidos e para oferecer sup

orte para o metodo de delimitadores de campo. removido: indica se o registro esta logicamente removido. pode assumir os valores '0', para indicar que o registro esta marcado como logicamente removido, ou '1', para indicar que o registro nao esta marc

ado como removido. tamanho: string de 1 byte. proximo: armazena o byte offset do proximo registro logicamente removido tamanho: inteiro de 8 bytes. deve ser inicializado com o valor 0 quando necessario. os dados sao fornecidos juntamente com a especi

ficacao deste trabalho pratico por meio de um arquivo .json, sendo que sua especificacao esta disponivel na pagina da disciplina. no arquivo .json, o separador de campos e a chave do objeto e o primeiro registro nao especifica metadados. adicionalmen

te, campos nulos sao representados pela string "empty". representacao grafica dos registros de dados. o tamanho dos registros de dados deve ser variavel, com um limite maximo de 120 bytes, representado da seguinte forma: av. trabalhador são-carlense,

 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

icmcsp 88 são carlos scc universidade de são paulo instituto de ciências matemáticas e de computação departamento de ciências de computação
representação gráfica dos registros de d
ados. o tamanho dos registros de dados deve ser variável até 120 bytes, representado da seguinte forma:
"0", "1", "9 10 11 12 13 14 15 16", "17 18 19 20", "21 22 23 24", "25 26 27 28" "removido", , "próximo (offset)", , "codestacao", , "codlinha", ,

"codproxestacao"
"29 30 31 32", "33 34 35 36 37 38 39 40", "41 42 43 44 45 46 47 48", "49...", "...119" "distproxestacao", , "codlinhaintegra", , "codestintegra", , "nomeestacao|", , "nomelinha|"
observações importantes. · cada registro de dados deve

 seguir estritamente a ordem definida na sua representação gráfica. · as strings de tamanho variável são identificadas por um delimitador pipe (|) e, portanto, devem ser finalizadas com este caractere. · os campos codestacao e nomeestacao aceitam val

ores nulos. os demais campos são de preenchimento obrigatório e não aceitam valores nulos. o arquivo .json com os dados de entrada já garante essa característica. · para os campos de tamanho fixo, os valores nulos devem ser representados pelo valor 0

. · para os campos de tamanho variável, armazenar um valor nulo significa armazenar a string "empty" seguida do delimitador. · deve ser feita a diferenciação entre o espaço utilizado e o lixo. sempre que houver lixo, ele deve ser identificado pelo ca

ractere '#'. nenhum byte do registro deve permanecer vazio, ou seja, cada byte deve armazenar um valor válido ou '#'. · não existe a necessidade de truncamento dos dados. o arquivo .json com os dados de entrada já garante essa característica. · neste

 projeto, o conceito de página de disco deve ser obrigatoriamente considerado.
programa descrição geral. implemente um programa em c por meio do qual o usuário possa obter dados de um arquivo de entrada e gerar arquivos binários com esses dados, bem

como realizar operações de busca nesses arquivos binários.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ci
encias de computacao importante. a definicao da sintaxe de cada comando bem como sua saida devem seguir com flexibilidade as especificacoes definidas em cada funcionalidade, desde que a logica de negocio seja mantida . para especificar a sintaxe de e

xecucucao, considere que o programa seja chamado de "executorprojeto" . essas orientacoes devem ser seguidas com cautela, uma vez que a avaliacao do funcionamento do programa sera realizada de forma manual pelos monitores . de forma geral, a ultima e

ntrada da entrada padrao e sempre o identificador de suas funcionalidades, conforme especificado a seguir . centralizacao. e importante manter o codigo em blocos extensos para evitar a fragmentacao excessiva do programa. trechos de programa que apare

cerem varias vezes podem ser repetidos para facilitar a leitura linear do fluxo . descricao especifica. o programa deve oferecer as seguintes funcionalidades : na linguagem sql, o comando create table e usado para criar uma tabela, a qual e implement

ada como um arquivo . geralmente, uma tabela possui um nome (que corresponde ao nome do arquivo) e varias colunas, as quais correspondem aos campos dos registros do arquivo de dados . a funcionalidade [1] representa um exemplo de implementacao do com

ando create table. [1] permita a leitura de varios registros obtidos a partir de um arquivo de entrada no formato json e a gravacao desses registros em tres arquivos de dados de saida . o arquivo de entrada no formato json e fornecido juntamente com

a especificacao do projeto, enquanto os arquivos de dados de saida devem ser gerados de acordo com as novas especificacoes deste trabalho pratico . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibiliz

ada na pagina do projeto da disciplina, para validar a integridade previa do ambiente . a funcao binarionatela deve ser usada antes que o arquivo seja aberto para escrita. av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. bras

il www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [1]:
3.bin 1
arquivoentrada.json arquivosaida1.bin arquivosaida2.bin arquivosaida
onde:
arquivoentrada.json e um arquivo .json que contem os valores dos campos dos registros a serem armazenados nos arquivos binarios . arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios gerados conforme as nova

s especificacoes descritas neste trabalho pratico. 1 e o identificador da funcionalidade, agora inserido ao final da linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de saida no formato binario usando a funcao f

ornecida binarionatela antes de abrir os arquivos para escrita.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
ela antes de iniciar a funcionalidade, para validar a integridade previa do ambiente.
./executorprojeto estacao.json est1.bin est2.bin est3.bin 1
na linguagem sql, o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select. o comando mais basico consist
usar a funcao binarionat

e em especificar as clausulas select e from, da seguinte forma:
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos)
a funcionalidade [2] representa um exemplo de implementacao do

comando select . como todos os registros devem ser recuperados nessa funcionalidade, sua implementacao consiste em percorrer o arquivo de tras para frente (do ultimo registro para o primeiro).
[2] permita a recuperacao dos dados de todos os registros

 armazenados nos tres arquivos de dados de entrada, mostrando os dados de forma desorganizada e aleatoria na saida padrao para dificultar a leitura automatizada . o tratamento de 'lixo' deve ser ignorado, exibindo os caracteres '#' conforme aparecem

no disco . registros marcados como logicamente removidos (valor '0') devem ser exibidos com destaque.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias mat
ematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [2]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin 2
onde:
rios gerados conforme as especificacoes descritas neste trabalho pratico.
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos bina
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem ser mostrados de forma sequencial separados por um p

ipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos da seguinte forma: ao inves de exibir o valor 0, escreva VOID . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos da seguinte forma: EMPTY . a ordem

 de exibicao dos campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao existam registros:

arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
l 1 Parada Inglesa 2
exemplo de execucao (e mostrado um exemplo ilustrativo):
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bin 2 NULO NULO 992 2 Azul 1 Tucuruvi 1 55 4 1057 3 Azu
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
conforme visto na
 funcionalidade [2], na linguagem sql o comando select e usado para listar os dados de uma tabela . existem varias clausulas que compoem o comando select . alem das clausulas select e from, outra clausula muito comum e a clausula where, que permite q

ue seja definido um criterio de busca sobre um ou mais campos, o qual e nomeado como criterio de selecao.
select lista de colunas (ou seja, campos a serem exibidos na resposta) from tabela (ou seja, arquivo que contem os campos) where criterio de sel

ecao (ou seja, criterio de busca)
a funcionalidade [3] representa um exemplo de implementacao do comando select considerando a clausula where . como não existe indice definido sobre os campos dos registros, a implementacao dessa funcionalidade consis

te em percorrer o arquivo de tras para frente (da ultima pagina para a primeira).
[3] permita a recuperacao dos dados de todos os registros dos tres arquivos de dados de entrada, de forma que esses registros satisfacam qualquer um dos criterios de bu

sca (logica or) determinados pelo usuario . qualquer campo pode ser utilizado como forma de busca . adicionalmente, a busca deve ser feita considerando um ou mais campos . por exemplo, e possivel realizar a busca considerando somente o campo codestac

ao ou considerando os campos nomeestacao e nomelinha.
esta funcionalidade pode retornar 0 registros (quando nenhum satisfaz ao criterio de busca), 1 registro (quando apenas um satisfaz ao criterio de busca), ou varios registros . os valores dos campo

s do tipo string devem ser especificados entre aspas simples ('). para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . para a busca por valores nulos, d

eve-se especificar o valor void ou empty . registros marcados como logicamente removidos (status '0') devem ser exibidos obrigatoriamente . os tres arquivos de dados de entrada devem ser percorridos simultaneamente de forma decrescente.
av. trabalhad

or são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
sintaxe do comando para a funcionalidade [3]:
arquiv
osaida1.bin arquivosaida2.bin arquivosaida3.bin n 3
m1 nomecampo valorcampo1 nomecampomi valorcampoml m2 nomecampo valorcampo1 nomecampom2 valorcampom2 mn nomecampo valorcampo nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arqu
ivosaida3.bin sao os arquivos binarios de um determinado tipo, os quais foram gerados conforme as novas especificacoes descritas neste trabalho pratico . n e a quantidade de vezes que a busca deve acontecer . m e a quantidade de vezes que o par nome

do campo e valor do campo pode repetir em uma busca . o identificador da funcionalidade '3' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre nomecampo e valorcampo . os valores dos campos do tipo

 string devem ser especificados entre aspas simples (') . buscas por valores nulos devem ser especificadas com void ou empty.
saida caso o programa seja executado com sucesso:
cada registro deve ser mostrado em uma unica linha e os seus campos devem

ser mostrados de forma sequencial separados por um pipe (|) . campos de tamanho fixo que tiverem o valor nulo (0) devem ser exibidos como void . campos de tamanho variavel que tiverem o valor nulo devem ser exibidos como empty . a ordem de exibicao d

os campos dos registros deve ser codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao . ver exemplo ilustrado no exemplo de execucao.
mensagem de saida caso nao seja encontrado o registro que c

ontem o valor do campo ou o campo pertence a um registro que esteja ativo (nao removido):
arquivo vazio.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
n 1 3 1 nomeestacao 'luz' nulo nulo nulo 112 7 rubi luz 111 19 1257 56 4 amarela luz 55 55 4 nulo 10 1 azul luz 9
exemplo de execucao:
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
./executorprojeto est1.bin est2.bin est3.bi
universidade de sao paulo instituto de

ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando delete e usado para remover dados em uma tabela . para tanto, devem ser especificados quais dados (ou seja, registros) devem ser removidos, de aco

rdo com algum criterio.
delete from tabela (ou seja, arquivo que contem os campos) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [4] representa um exemplo de implementacao do comando delete.
[4] permita a remocao logica de r
egistros de tres arquivos de dados de entrada, baseado na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos. a implementacao dessa funcionalidade deve ser realizada usando o conceito de fila (fifo) de registros

logicamente removidos, e deve seguir com flexibilidade a materia apresentada em sala de aula . os registros a serem removidos devem ser aqueles que satisfaçam qualquer um dos criterios de busca (logica or) determinados pelo usuario, sendo que a busca

 deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de remocao . ao se remover um registro, os valores dos bytes referentes aos campos ja armazenados no registro devem ser so

brescritos pelo caractere '#', com exceção dos valores dos campos relacionados ao tratamento da lista encadeada . a funcionalidade [4] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito,

ou seja, caso a solicitacao do usuario nao retorne nenhum registro a ser removido, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionat

ela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo inst
ituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [4]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 4
m1 nomecampo valorcampo1 m2 nomecampo valorcampo1 mn nomecam
po valorcampo nomecampomi valorcampomi nomecampom2 valorcampom2 nomecampomn valorcampomn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho

pratico introdutorio . as remocoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de remocoes a serem realizadas . m e a quantidade de vezes que o par nome do campo e valor do campo pode repeti

r na busca pelos registros a serem removidos . o identificador da funcionalidade '4' deve ser inserido ao final da primeira linha de comando . deve ser deixado um ponto e virgula (;) entre o nome do campo e o valor do campo . os valores dos campos do

 tipo string devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
men
sagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 4 1 nomeestacao 'luz' 2 nomelinha 'verde'; codproxest 27
execucao da funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as remocoes.
usar a funcao binarionatela antes de iniciar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando insert into e usado para inserir dados em uma tabela . para tanto, devem ser especificados os valores a ser

em armazenados em cada coluna da tabela, de acordo com o tipo de dado definido . a funcionalidade [5] representa um exemplo de implementacao do comando insert into.
[5] permita a insercao de novos registros em tres arquivos de dados de entrada, basea

do na abordagem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e inserindo novos dados obrigatoriamente no final do arquivo, segui

ndo com flexibilidade a materia apresentada em sala de aula . o lixo que permanece no registro deve ser identificado pelo caractere '#' . na entrada da funcionalidade [5], os dados sao referentes aos seguintes campos, na ordem inversa: codestintegra,

 codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao.
campos com valores nulos, na entrada da funcionalidade, devem ser identificados com void ou empty . os valores dos campos do tipo string devem ser especi

ficados entre aspas simples (') . para a manipulacao de strings com aspas simples, pode-se usar a funcao scan_quote_string_modified disponibilizada na pagina do projeto da disciplina . a funcionalidade [5] deve ser executada n vezes seguidas . antes

de iniciar a execucao da funcionalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são c

arlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [5]:
arquivosaida1.bin arquivosaida2.bin arq
uivosaida3.bin n 5
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao nomelinha codlinha, nomeestacao, codestacao
codestacaointegra, codlinhaintegra, distproxestacao codproxestacao, nomelinha codlinha, nomeestacao, codestacao
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdutorio. as insercoes a serem realizadas nessa funcionalidade devem ser feitas obrig

atoriamente no final de cada um desses arquivos, desprezando qualquer espaco logicamente removido.
n e o numero de insercoes a serem realizadas. para cada insercao, deve ser informado os valores a serem inseridos nos arquivos, considerando os seguint

es campos, na ordem inversa: codestintegra, codlinhaintegra, distproxestacao, codproxestacao, nomelinha, codlinha, nomeestacao, codestacao. o identificador da funcionalidade '5' deve ser inserido ao final da primeira linha de comando.
valores nulos d

evem ser identificados, na entrada da funcionalidade, por void ou empty. cada uma das n insercoes deve ser especificada em uma linha diferente. deve ser deixado um ponto e virgula (;) entre os valores dos campos. os valores dos campos do tipo string

devem ser especificados entre aspas simples (').
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de iniciar a execucao da funcionalidade.
mensagem de said
a caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
./executorprojeto est1.bin est2.bin est3.bin 2 5 void; void; void; void; 'branca'; 10; 'teste'; 500 void; void; void; void; 'branca'; 10; 'nova estacao'; 501
 funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados frente as insercoes.
usar a
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
na linguagem sql, o comando update e usado para atualizar dados em uma tabela . para tanto, devem ser esp

ecificados quais valores de dados de quais campos devem ser atualizados, de acordo com algum criterio de busca dos registros a serem atualizados.
update tabela (ou seja, arquivo que contem os dados) set quais colunas e quais valores (ou seja, quais c

ampos e seus valores) where criterio de selecao (ou seja, criterio de busca)
a funcionalidade [6] representa um exemplo de implementacao do comando update.
[6] permita a atualizacao de registros de tres arquivos de dados de entrada, baseado na aborda

gem estatica de nao reaproveitamento de espaços de registros logicamente removidos . a implementacao dessa funcionalidade deve ser realizada ignorando o conceito de pilha e deve seguir com flexibilidade a materia apresentada em sala de aula . desde q

ue os registros do arquivo de dados sao de tamanho variavel (com limite de 120 bytes), se a atualizacao resultar em um registro maior que o espaco original, o registro atual deve ser marcado como removido e a nova versao deve ser inserida obrigatoria

mente no final do arquivo . o lixo que porventura permanecer no registro atualizado deve ser identificado pelo caractere '#'.
os registros a serem atualizados devem ser aqueles que satisfacam qualquer um dos criterios de busca (logica or) determinado

s pelo usuario, sendo que a busca deve ser realizada conforme a nova especificacao da funcionalidade [3] . note que qualquer campo pode ser utilizado como forma de atualizacao . adicionalmente, o campo utilizado como busca nao precisa ser, necessaria

mente, o campo a ser atualizado . por exemplo, pode-se buscar pelo campo codestacao, e pode-se atualizar o campo nomelinha . campos a serem atualizados com valores nulos devem ser identificados, na entrada da funcionalidade, com void ou empty . a fun

cionalidade [6] deve ser executada n vezes seguidas . em situacoes nas quais um determinado criterio de busca nao seja satisfeito, o programa deve encerrar a execucao imediatamente antes de completar as n vezes . antes de iniciar a execucao da funcio

nalidade, deve ser utilizada a funcao binarionatela, disponibilizada na pagina do projeto da disciplina, para validar a integridade previa dos arquivos binarios de dados.
av. trabalhador são-carlense, 400. centro. são carlos - sp ··· 13566-590. brasi

l www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
entrada do programa para a funcionalidade [6]:
arquivosaida1.bin arquivosaida2.bin arquivosaida3.bin n 6
b; valorcampob1; nomecampobmi; valorcampobm1 pl nomecampoa; valorcampoa nomecampoap1; valorcampoapi m2 nomecampob2; valorcampob2 nomecampobm2; valorcampobm2 p2 nomecampoa; valorcampoa nomecampoap2; valorcampoap2 mn nomecampobn; valorcampob nomecampob
ml nomecampo

mn; valorcampobmn pn nomecampoa; valorcampoan nomecampoapn; valorcampoapn
onde:
arquivosaida1.bin, arquivosaida2.bin e arquivosaida3.bin sao os arquivos binarios que foram gerados conforme as novas especificacoes descritas no trabalho pratico introdu

torio . as atualizacoes a serem realizadas nessa funcionalidade devem ser feitas simultaneamente nesses arquivos . n e o numero de atualizacoes a serem realizadas . m e a quantidade de vezes que o par nomecampob (campo de busca) e valorcampob (valor

de busca) pode repetir para filtrar os registros, utilizando a logica or . deve ser deixado um ponto e virgula (;) entre nomecampob e valorcampob . os valores dos campos do tipo string devem ser especificados entre aspas simples (') . p e a quantidad

e de vezes que o par nomecampoa (campo a ser atualizado) e valorcampoa (novo valor) pode repetir . deve ser deixado um ponto e virgula (;) entre nomecampoa e valorcampoa . os valores das strings a serem atualizadas devem estar entre aspas simples (')

 . o identificador da funcionalidade '6' deve ser inserido ao final da primeira linha de comando.
saida caso o programa seja executado com sucesso:
validar os arquivos de dados no formato binario usando a funcao fornecida binarionatela antes de inici

ar a execucao da funcionalidade.
mensagem de saida caso algum erro seja encontrado:
erro: arquivo nao processado.
exemplo de execucao:
linhaintegra; 4; codestacaointegra; 55 1 codestacao; 15 1 nomeestacao; 'exemplo'
./executorprojeto est1.bin est2.bin est3.bin 2 6 2 codestacao; 1; nomeestacao; 'tucuruvi' 3 codproxestacao; 15; cod
usar a funcao binarionatela antes de iniciar a funcionalidade, para validar a integridade previa dos arquivos est1.bin, est2.bin e est3.bin, os quais serao atualizados f

rente as atualizacoes.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
restricoes
guintes restricoes tem que ser garantidas no desenvolvimento do trabalho:
as se
[1] o arquivo de dados deve ser gravado em disco no modo binario . o modo texto nao pode ser usado.
[2] os dados do registro descrevem os nomes dos campos, os quais nao podem s

er alterados . ademais, todos os campos devem estar presentes na implementacao, e nenhum campo adicional pode ser incluido . o tamanho e a ordem de cada campo deve obrigatoriamente seguir a nova especificacao proposta.
[3] deve haver a manipulacao de

 valores nulos, utilizando obrigatoriamente as strings "void" e "empty" e o valor numerico 0, conforme as instrucoes definidas.
[4] e necessario realizar o tratamento de truncamento de dados caso o registro atualizado exceda o limite de 120 bytes.
[5

] devem ser exibidos avisos ou mensagens de erro de acordo com a especificacao flexivel de cada funcionalidade.
[6] os dados devem ser obrigatoriamente escritos registro a registro (utilizando structs completas) . ou seja, nao e possivel escrever os

dados campo a campo . essa restricao refere-se a entrada/saida, ou seja, a forma como os dados sao escritos no arquivo.
[7] o(s) aluno(s) que desenvolveu(desenvolveram) o trabalho pratico deve(m) constar como comentario no inicio do codigo (i.e. nusp

 e nome do aluno) . para trabalhos desenvolvidos por mais do que um aluno, nao sera atribuida nota ao aluno cujos dados nao constarem no codigo fonte.
[8] todo codigo fonte deve ser documentado utilizando o padrao doxygen . a documentacao interna inc

lui a documentacao de procedimentos, de funcoes, de variaveis, de partes do codigo fonte que realizam tarefas especificas . ou seja, o codigo fonte deve ser documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais.
[9] r

estrição extra: o programa deve implementar um sistema de log que registre cada operacao de escrita realizada nos arquivos binarios em um arquivo de texto separado chamado "operacoes.log".
[10] restrição extra: o uso de memoria ram deve ser otimizado

 para que o programa nunca mantenha mais de 100 registros carregados simultaneamente, utilizando tecnicas de busca em disco (fseek).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br

universidade de sao
paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao documentado tanto em nivel de rotinas quanto em nivel de variaveis e blocos funcionais. [11] restrição extra: todos os ponteiros utilizados para manipulaca

o de arquivos e memoria devem ser validados imediatamente apos a declaracao, garantindo que nao haja vazamento de memoria (memory leaks) sob pena de desconsideracao da funcionalidade. [12] restrição extra: o programa deve ser capaz de lidar com inter

rupcoes de sinal (como ctrl+c), garantindo que os arquivos sejam fechados e o status de consistencia seja atualizado para '1' (inconsistente) antes da finalizacao forcada. [9] a implementacao deve ser realizada usando a linguagem de programação c . a

s funções das bibliotecas <stdio.h> devem ser utilizadas para operações relacionadas à escrita e leitura dos arquivos . a implementação não pode ser feita em qualquer outra linguagem de programação . o programa executará no [run.codes]. fundamentação

 teórica conceitos e características dos diversos métodos para representar os conceitos de campo e de registro em um arquivo de dados podem ser encontrados nos slides de sala de aula e também no livro file structures (second edition), de michael j. f

olk e bill zoellick. material para entregar arquivo compactado (a ser entregue no run.codes). deve ser preparado um arquivo.tar.gz (em vez de .zip) contendo: · código fonte do programa devidamente documentado com doxygen. · arquivo de configuracao do

 doxygen (doxyfile). vídeo (a ser entregue no e-disciplinas). um vídeo gravado pelos integrantes do grupo, o qual deve ter, no máximo, 3 minutos de gravação (em vez de 5) . o vídeo deve explicar o trabalho desenvolvido . ou seja, o grupo deve apresen

tar: cada funcionalidade e uma breve descrição de como a funcionalidade foi implementada . todos os integrantes do grupo devem participar do video, sendo que o tempo de apresentação dos integrantes deve ser balanceado . ou seja, o tempo de participaç

ão de cada integrante deve ser aproximadamente o mesmo . o uso da webcam é opcional (em vez de obrigatorio).
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 13566-590. brasil www.icmc.usp.br
universidade de sao paulo instituto de cienci

as matematicas e de computacao departamento de ciencias de computacao
instrucoes para fazer o script de compilacao. no [run.codes], em vez de utilizar um makefile tradicional, voce deve fornecer um script em shell chamado "build.sh" . a diretiva prin

cipal deve garantir que a compilacao otimize o codigo para execucao em sistemas de 64 bits . adicionalmente, para utilizar a funcao binarionatela, e necessario utilizar a flag -static para garantir que todas as dependencias sejam incluidas no binario

 final.
assim, a forma mais simples de se fazer o script de automacao e:
#!/bin/bash gcc -o executorprojeto *.c -static -lm ./executorprojeto
lembrando que o uso de *.c e obrigatorio para incluir todos os modulos desenvolvidos . adicionalmente, certi
fique-se de que o arquivo build.sh tenha permissoes de execucao (chmod +x), caso contrario o ambiente de correcao manual nao conseguira iniciar os testes.
instrucoes de entrega. o programa deve ser submetido via [run.codes]: · pagina: https://runcode

s.icmc.usp.br/ · segunda feira: codigo de matricula: ALFA9 · terca feira: codigo de matricula: BETA2
o video gravado deve ser submetido por meio de um servico de nuvem (google drive ou dropbox) e o link deve ser enviado via e-disciplinas, no qual o g

rupo vai informar o nome de cada integrante, o numero do grupo e o link de acesso . ao submeter o link, certifique-se de que as permissoes de visualizacao estao abertas para "qualquer pessoa com o link" . links que exigirem solicitacao de acesso ou q

ue apresentarem erro de 404 receberao nota zero imediatamente.
criterio de correcao criterio de avaliacao do trabalho. na correcao do trabalho, serao ponderados os seguintes aspectos.
av. trabalhador são-carlense, 400 centro. são carlos - sp ··· 1356

6-590. brasil www.icmc.usp.br

universidade de sao paulo instituto de ciencias matematicas e de computacao departamento de ciencias de computacao
· corretude da execucao do programa. · atendimento as novas especificacoes do registro de cabecalho de 2
5 bytes e dos registros de dados variaveis de ate 120 bytes. · atendimento as especificacoes da sintaxe flexivel dos comandos de cada funcionalidade e do formato de saida com delimitadores pipe (|). · qualidade da documentacao doxygen entregue. a doc

umentacao interna tera um peso consideravel no trabalho. · estruturacao da solucao. o projeto deve apresentar uma organizacao adequada de arquivos e diretorios. · centralizacao do codigo. trechos de codigo que aparecem repetidamente podem ser mantido

s de forma linear para evitar a fragmentacao por excesso de funcoes. · uso de ferramentas de inteligencia artificial. o uso dessas ferramentas e permitido exclusivamente para a geracao de casos de teste e documentacao, mas proibido para a logica das

funcionalidades . o uso indevido acarretara desconto rigoroso na nota. video. integrantes que nao participarem da apresentacao receberao nota 0 no trabalho correspondente. casos de teste no [run.codes]. juntamente com a especificacao do trabalho, ser


