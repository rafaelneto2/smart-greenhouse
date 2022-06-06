# smart-greenhouse
ESTUFA AUTOMATIZADA COM IoT, FIREBASE E ESP8266

## Sobre o projeto
Essa pesquisa tem como objetivo apresentar um protótipo de uma estufa automatizada de baixo custo com uso de Internet das Coisas (IoT), para controle, informação e visualização de dados. Essa pesquisa foi desenvolvida em 2019 com uso de microcontrolador com conexão Wi-Fi, além de sensores e atuadores responsáveis por mensurar e manter a estufa em seu funcionamento ideal para o cultivo de plantas. Neste projeto, utiliza-se um banco de dados em tempo real oferecido pelo Google Firebase para armazenar os dados coletados, bem como um website hospedado nos servidores da Google para acompanhar o funcionamento de todos os sensores e atuadores. Como resultado, foi possível controlar a umidade do ar, umidade do solo, temperatura, ventilação e irrigação através do sistema WEB, o qual foi utilizado para controle e visualização das variáveis do sistema em tempo real visando comodidade e praticidade para o usuário

## Materiais utilizados
*  Plataforma ESP8266
*  Sensores e atuadores
*  IDE Arduino
*  Firebase Realtime Database
*  Sistema WEB
*  Firebase Hosting

## Resultados
O protótipo da estufa foi projetado para controlar variáveis 
internas para se obter um ambiente ideal para o crescimento saudável das plantas cultivadas. O sensor coleta os dados das variáveis a cada 10 minutos. Quando um valor mínimo de umidade do solo (definido pelo usuário) for atingido e a terra secar, a válvula solenidade é acionada até que a umidade chegue ao valor máximo determinado pelo usuário previamente. Neste caso, a válvula é desativada e o ciclo ser repete novamente. Além disso, a temperatura também é monitorada e quando atinge valores altos o cooler é ligado para refrigerar o ambiente. Caso contrário, a lâmpada é ligada para aquecer a estufa nos casos em que a temperatura fica abaixo de um valor pré-definido pelo usuário. Outra ação acontece quando a umidade do ar aumenta muito e, neste caso, o cooler também é acionado para que a entrada de ar do ambiente externo entre dentro da estufa.

### Protótipo
![image](https://user-images.githubusercontent.com/26224729/172183875-3f825291-07d3-4d6c-9e97-82cb18cd01b9.png)


### Dashboard
O protótipo permite também que os dados coletados e as ações dos atuadores sejam registradas em tempo real, através de um website hospedado nos servidores da Google pelo Firebase Hosting. Todo o sistema foi controlado pelo ESP8266 que é responsável por fazer a leitura dos sensores, interpretá-las e comandar os relés que fazem a interrupção dos atuadores. Além disso, o ESP8266 também envia os dados a um banco de dados hospedado nos servidores da Google, os quais são armazenados para o usuário durante um período de 30 dias no Firebase Realtime, para que ele possa gerenciá-los facilmente através de uma aplicação WEB.


![image](https://user-images.githubusercontent.com/26224729/172183758-8e4a847c-902f-45c9-a015-3cd338910067.png)


### Mudas após 30 dias
![IMG_20200530_122521196_HDR (2)](https://user-images.githubusercontent.com/26224729/172184588-c7b9b696-f3ea-48f5-a1e9-7fdb4bcf8264.jpg)

Além disso, o projeto foi desenvolvido para aplicações de baixo custo, sendo uma importante aplicação para produtores rurais de pequeno porte e usuários residenciais. Todo o projeto de hardware pode ser obtido com um valor aproximado de R$ 287,00.


