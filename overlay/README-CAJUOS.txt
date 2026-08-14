CAJUOS GB300 v0.3.3 — OVERLAY DE CARTAO

Este ZIP NAO e uma imagem de disco. Nao use Rufus, Etcher ou dd.

1. Faça uma copia integral de um cartao GB300 que ja inicia no seu console.
2. Formate somente se voce possuir a imagem/backup apropriado da sua revisao v1/v2.
3. Extraia este pacote NA RAIZ da copia do cartao, mesclando diretorios.
4. Preserve ROMS/, saves/, BIOS pessoais e quaisquer arquivos do cartao original.
5. O diretorio ROMS/ e criado apenas como estrutura vazia; ele nao contem jogos.
6. Use FAT32 e mantenha o console desligado ao inserir/remover o cartao.

O primeiro teste deve ser somente boot, menu e controles. Se ocorrer tela preta
antes do menu, restaure a copia original: nao tente corrigir com frameskip,
clock de CPU, perfis UHS ou troca de BIOS.

O perfil padrao usa ROMS/ somente, audio ligado, Snes9x2002 para SNES, QPSX
para PS1, GE 198 MHz e backlight 50. Perfis de SD agressivos continuam fora
do padrao de diagnostico.

FORMATOS RECOMENDADOS
GBA: ROMS/GBA/*.gba
SNES: ROMS/SFC/*.sfc ou *.smc
MEGA DRIVE: ROMS/MD/*.md, *.gen, *.smd ou *.bin
PC ENGINE: ROMS/PCE/*.pce ou *.sgx
PS1/QPSX: ROMS/PS/*.cue com o *.bin correspondente na mesma pasta.
Quando CUE e BIN coexistirem, o driver CajuOS prioriza o CUE para QPSX.
O BIN de Mega Drive permanece associado ao PicoDrive por estar em ROMS/MD.
