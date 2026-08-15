# CajuOS GB300 — source e build

Este diretório contém uma cópia editável do source **UniFrog v0.5.2** com as alterações do CajuOS para o GB300. O código não é um Linux completo: ele é um firmware HCRTOS/MIPS para o hardware da família DataFrog/SF2000/GB300.

## O que foi adicionado

O source inclui um **menu pré-jogo nativo**. Ao selecionar uma ROM e escolher o core, o frontend apresenta uma etapa intermediária com estas opções:

| Opção | Função |
|---|---|
| Start game | Inicia a ROM com as escolhas atuais. |
| Performance | Compatibility, Balanced, Performance ou Ultra. |
| CPU | Seleciona clocks suportados pelo runtime. |
| GPU | Seleciona o perfil de clock do GE. |
| Frameskip | Off, Auto, Fixed 1 ou Fixed 2. |
| Audio | Ativa ou silencia o áudio. |
| Duplicate frames | Evita reapresentar frames visualmente repetidos quando habilitado. |
| Back | Retorna para a seleção de core. |

O host libretro traduz o perfil escolhido para opções disponíveis em cada core. Opções que não existirem em um core são ignoradas de forma segura. O perfil também pode configurar renderer rápido, filtros de áudio, transparência, limite de sprites, frameskip interno e overclock compatível quando a opção estiver exposta pelo core.

A política de frames repetidos usa uma assinatura amostrada do framebuffer. Ela reduz chamadas ao presenter/GE em cenas estáticas, menus e frames sem alteração. Não é apresentada como um aumento mágico da potência do emulador: quando o gargalo está dentro da CPU emulada, a otimização correta continua sendo o core, o dynarec ou a redução de efeitos no próprio core.

## Dependências

O build requer Linux, `git`, `make`, `gcc`, `device-tree-compiler`, `curl`, `xz-utils`, `zip`, `patch` e ferramentas Unix usuais. A toolchain MIPS é baixada automaticamente pelo alvo `ci-toolchain` a partir da versão pinada no Makefile. O SDK HCRTOS pode ser baixado pelo alvo `deps-sdk`, mesmo quando o source foi obtido como ZIP e não possui um checkout Git com submódulo inicializado.

## Build reproduzível

A partir da raiz deste diretório:

```sh
cd source/UniFrog-v0.5.2
make deps-sdk
make deps
make ci-toolchain
make quick-check
make
make sd-zip
```

O artefato é gerado em:

```text
source/UniFrog-v0.5.2/output/UniFrog-sdcard.zip
```

Esse ZIP é um **overlay de cartão SD**, não uma imagem bruta. Faça backup integral do cartão original, extraia o ZIP na raiz de uma cópia FAT32 e preserve ROMs, saves e BIOS legítimas.

## Testes

`make quick-check` executa o doctor do ambiente, o core smoke, as verificações do frontend nativo, o runtime JS2300 e o teste de boot logo. O build MIPS e o empacotamento são verificáveis no host, mas nenhuma compilação em ambiente de host substitui um boot físico no GB300. Boot, tela, áudio, controles, consumo, estabilidade de clock e compatibilidade de cada ROM ainda devem ser testados no hardware.

## Licenças

O source mantém o `LICENSE.txt`, `THIRD_PARTY.md` e as licenças dos componentes upstream. Os cores possuem licenças distintas; redistribua o código, binários e dependências conforme os avisos correspondentes.
