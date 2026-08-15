# CajuOS GB300 4.0

## Resumo

O **CajuOS GB300 4.0** é uma distribuição independente de firmware, frontend, cores, configurações e ferramentas para o console GB300. O projeto possui sua própria árvore de source e seu próprio processo de build. Outros sistemas podem ser usados como referência técnica de compatibilidade, mas não definem a identidade do CajuOS.

A distribuição final é um **overlay de cartão SD**, não uma imagem bruta. O usuário deve extrair o conteúdo do ZIP diretamente na raiz de uma cópia FAT32 do cartão original.

## Menu pré-jogo e desempenho

Depois de selecionar uma ROM, o frontend mostra o menu antes do lançamento. O usuário pode escolher o perfil Compatibility, Balanced, Performance ou Ultra, além de CPU, GPU/GE, frameskip, áudio e descarte de frames repetidos. As configurações ficam salvas no cartão.

O CajuOS aplica apenas opções de desempenho registradas pelo core selecionado. O mecanismo de frames repetidos usa uma assinatura amostrada do framebuffer para evitar reapresentar uma imagem que não mudou. Esse mecanismo reduz trabalho do presenter/GE em telas estáticas, mas não elimina o custo da CPU emulada nem substitui o teste no console físico.

## Instalação

Faça uma cópia integral do cartão original. Extraia **os arquivos dentro de** `CajuOS-GB300-v4.0-sdcard.zip` diretamente na raiz da cópia. Após a extração, os diretórios `unifrog/`, `unifrog_data/`, `ROMS/` e `bios/` devem estar na raiz do cartão. Esses nomes de diretório são contratos de compatibilidade do boot/runtime do GB300; não significam que o projeto CajuOS seja outro sistema.

Não use Rufus, Etcher ou `dd` para gravar o ZIP como imagem. Não coloque o ZIP dentro de outra pasta. Preserve ROMs, saves e BIOS legítimas. Caso o aparelho não inicialize, desligue, restaure o backup e não continue usando o pacote naquela variante sem coletar diagnóstico.

## Source e build

A árvore pública está em `source/CajuOS-GB300-v4.0`. Para compilar:

```sh
cd source/CajuOS-GB300-v4.0
make deps-sdk
make deps
make ci-toolchain
make quick-check
make verify
make
cd ../..
CAJUOS_VERSION=4.0 ./scripts/build-cajuos-release.sh
```

O pacote fonte separado é `release/CajuOS-GB300-source-v4.0.zip`. O pacote SD é `release/CajuOS-GB300-v4.0-sdcard.zip`.

## Validação

A validação host inclui doctor do ambiente, core smoke, frontend nativo, JS2300, boot logo, link layout, fastboot, compilação dos cores, geração do firmware, teste de integridade do ZIP, inspeção do layout extraído em uma pasta vazia e comparação dos caminhos técnicos com o pacote de referência usado no desenvolvimento.

Essa validação não substitui o teste físico. Boot real, tela, áudio, controles, estabilidade térmica, autonomia, clocks e desempenho de cada jogo precisam ser confirmados em um GB300 físico.
