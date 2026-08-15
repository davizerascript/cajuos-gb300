CajuOS GB300 4.1 — INSTALAÇÃO RÁPIDA

Este ZIP e um pacote de arquivos para cartao SD. Ele NAO e uma imagem de disco.
Nao use Rufus, Etcher ou dd para gravar este ZIP.

1. Desligue o GB300 e faca uma copia integral do cartao original.
2. Abra CajuOS-GB300-v4.1-sdcard.zip no computador.
3. Extraia os itens de dentro do ZIP diretamente na raiz da copia do cartao.
4. Nao deixe o conteudo dentro de uma pasta intermediaria com o nome do ZIP.
5. Preserve ROMS/, saves, BIOS pessoais e arquivos da revisao do seu console.
6. Ejete o cartao com seguranca antes de coloca-lo novamente no GB300.

A raiz correta deve conter:

Caju OS/
Caju OS Data/
ROMS/
bios/
README-CAJUOS.txt
REPRODUCE-CAJUOS.txt

O firmware publico esta em Caju OS/firmware/cajuos.bin.
As configuracoes, scripts, idiomas, saves, logs e dados ficam em Caju OS Data/.
Nao renomeie essas duas pastas depois da instalacao.

ROMs nao sao distribuidas pelo CajuOS. Copie somente conteudo que voce possui legalmente:

GBA: ROMS/GBA/*.gba
SNES: ROMS/SFC/*.sfc ou *.smc
MEGA DRIVE: ROMS/MD/*.md, *.gen, *.smd ou *.bin
PC ENGINE: ROMS/PCE/*.pce ou *.sgx
PS1/QPSX: ROMS/PS/*.cue com os *.bin correspondentes na mesma pasta
NES: ROMS/NES/*.nes
GAME BOY: ROMS/GB/*.gb ou *.gbc

Para o primeiro boot, teste apenas imagem, menu e controles. Ao abrir uma ROM,
use o perfil Balanced e selecione Start game. Depois teste Compatibility,
Performance e Ultra conforme a necessidade do jogo.

Se ocorrer tela preta antes do menu, reinicio, travamento no logo ou perda de
controles, desligue o console e restaure a copia original. Nao tente corrigir
uma falha de boot alterando frameskip, clock, BIOS ou parametros do cartao.

Tutorial completo:
https://github.com/davizerascript/cajuos-gb300/blob/main/docs/INSTALL-CajuOS-GB300.md
