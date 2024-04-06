# Edge Computing Challenge Sprint 3 - HP Quadrinhos

> Status: Developed

<img width="479" alt="image" src="https://github.com/LanaAndrade/hpQuadrinhos-Challenge-Edge/assets/82892986/579d5fd4-ed9a-42c0-8425-95d2d0c58835">

O caso apresentado trata-se de uma parceria com o hospital das clínicas da USP, que busca solucionar o problema da falta de informação dos pacientes infantis sobre os exames, através de histórias em quadrinhos humanas, lúdicas e informativas.

Nós escolhemos integrar o projeto de IOT de forma lúdica a adaptada para a idade das crianças.

O input será feito através de um potenciômetro, que é conectado a uma Led rgb, e conforme a criança altera o valor do potenciômetro, a cor da Led muda. Primeiramente, a criança escolherá qual história ela deseja ler, através da cor, como por exemplo, ciano para a aventura de amelie no mundo dos microscópios.

Após a história ser escolhida, a história será enviada para o node-red, para um Dashboard de quantas vezes cada história foi escolhida.

Assim que a criança terminar de ler a história, ela alterará a cor para sinalizar que acabou, e assim, avaliar a história.

Assim, o tempo que a criança passou lendo a história será calculado e enviado ao mqtt, para que o node-red calcule a média de tempo que as crianças passaram lendo as histórias. E também, para que nós tenhamos gráficos para o feedback das crianças sobre as histórias, através de sua avaliação também pelo sistema de cores.

Esse é são os gráficos do node-red das histórias, como podemos ver, temos funções para calcular a quantidade de histórias escolhidas, qual foi a história mais escolhida, assim como a média do tempo que as crianças passaram lendo as histórias, e as médias das avaliações de cada história, assim como a de avaliações totais.

## Componentes
* ESP32
* 1 LED RGB (utilizado para guiar as crianças em qual valor estão escolhendo)
* 1 Potenciômetro (Utilizado para captar os inputs dos pacientes)
* 3 Resistores de 220kΩ (Utilizados no LED)
* 10 Cabos Jumper Macho x Fêmea
  
## Desenvolvimento
O projeto foi desenvolvido utilizando a plataforma Wokwi para a montagem do esquema e para a codificação. O projeto será validado no dia 05/04/2023 pelo professor responsável.

## Código Fonte
[Link para o simulador](https://wokwi.com/projects/394103961130029057)

### Vídeo do Projeto
<a href="https://www.youtube.com/watch?v=dyoQjkK6Q2E"><img src="https://github.com/LanaAndrade/hpQuadrinhos-Challenge-Edge/assets/82892986/579d5fd4-ed9a-42c0-8425-95d2d0c58835" alt="Whats-App-Image-2023-10-30-at-19-44-49" border="0"></a>

## Desenvolvedores

Desenvolvedor | RM
:-----------: | :------:
Caio Freitas  | 553190
Felipe Santana| 554259
Lana Andrade  | 552596
Lucas Garcia  | 554070
Mateus Tibão  | 553267
