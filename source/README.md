# CajuOS GB300 4.0 — source e build

Este diretório contém a árvore de desenvolvimento do **CajuOS GB300 4.0**. O CajuOS é um projeto independente de firmware, frontend, cores, configurações e ferramentas para o GB300. Alguns nomes internos de compatibilidade permanecem no código porque fazem parte do contrato de boot, do carregador de módulos e das APIs do hardware; esses nomes não representam a identidade ou a origem do projeto.

## Estrutura

A implementação principal está em `source/CajuOS-GB300-v4.0`. A pasta contém o firmware MIPS/HCRTOS, o frontend nativo, o host de emulação, os cores, as ferramentas de imagem e o Makefile de build. O diretório `overlay/` contém a camada de distribuição do CajuOS: idioma, temas, diagnósticos, configurações, scripts e arquivos de instalação no cartão SD.

O CajuOS não é um Linux completo. Ele é um firmware HCRTOS/MIPS para a família de hardware do GB300. O ZIP final é um **overlay de cartão SD**: os diretórios `unifrog/` e `unifrog_data/` são nomes de compatibilidade exigidos pelo boot e pelo runtime do aparelho, não uma declaração de que o CajuOS seja outro sistema.

## Menu pré-jogo

Depois de selecionar uma ROM, o frontend apresenta uma etapa antes do lançamento com estas opções:

| Opção | Função |
|---|---|
| Start game | Inicia a ROM com as escolhas atuais. |
| Performance | Compatibility, Balanced, Performance ou Ultra. |
| CPU | Seleciona clocks suportados pelo runtime. |
| GPU | Seleciona o perfil de clock do GE. |
| Frameskip | Off, Auto, Fixed 1 ou Fixed 2. |
| Audio | Ativa ou silencia o áudio. |
| Duplicate frames | Evita reapresentar frames visualmente repetidos quando habilitado. |
| Back | Retorna para a tela anterior. |

O host aplica as opções de desempenho que cada core registrar. Opções ausentes são ignoradas de forma segura. A política de frames repetidos usa uma assinatura amostrada do framebuffer para reduzir chamadas ao presenter/GE em cenas estáticas; ela não é apresentada como aumento mágico da potência da CPU emulada.

## Dependências

O build requer Linux, `git`, `make`, `gcc`, `device-tree-compiler`, `curl`, `xz-utils`, `zip`, `patch` e ferramentas Unix usuais. A toolchain MIPS é baixada pelo alvo `ci-toolchain`. O SDK HCRTOS é baixado pelo alvo `deps-sdk` mesmo quando o source é obtido como ZIP e não possui metadata de submódulo inicializada.

## Build reproduzível

A partir da raiz do repositório:

```sh
cd source/CajuOS-GB300-v4.0
make deps-sdk
make deps
make ci-toolchain
make quick-check
make verify
make
make sd-zip
cd ../..
CAJUOS_VERSION=4.0 ./scripts/build-cajuos-release.sh
```

O artefato de firmware intermediário sai em `source/CajuOS-GB300-v4.0/output/`. O pacote final de cartão SD sai em `release/CajuOS-GB300-v4.0-sdcard.zip`.

## Instalação

Faça backup integral do cartão original. Extraia **o conteúdo** de `CajuOS-GB300-v4.0-sdcard.zip` diretamente na raiz de uma cópia FAT32 do cartão, de modo que `unifrog/`, `unifrog_data/`, `ROMS/` e `bios/` fiquem na raiz. Não crie uma pasta adicional contendo o ZIP inteiro. Preserve ROMs, saves e BIOS legítimas.

## Testes e limites

`make quick-check` e `make verify` validam a compilação, o link, o layout de memória, os cores, o frontend e o empacotamento no host. Testes de ROM no host podem validar o carregamento e a lógica de seleção, mas não substituem um boot físico. Tela, áudio, controles, estabilidade térmica, autonomia, clocks reais e compatibilidade de cada ROM precisam ser confirmados no GB300.

## Licenças

A árvore mantém os avisos de licença dos componentes técnicos e dos cores. Redistribua o código, binários e dependências de acordo com os avisos correspondentes em `LICENSE`, `THIRD_PARTY.md` e nas pastas de cada componente.
