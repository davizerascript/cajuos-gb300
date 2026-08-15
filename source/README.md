# CajuOS GB300 — árvore fonte 4.1

Esta pasta contém a árvore de código do **CajuOS GB300 4.1**, um firmware HCRTOS/MIPS para o console portátil GB300. O projeto é independente e possui frontend nativo, host Libretro, cores, Performance Manager, menu pré-jogo, ferramentas de diagnóstico e scripts de reprodução.

A distribuição final usa duas pastas públicas no cartão SD:

```text
Caju OS/
Caju OS Data/
```

Os nomes das pastas são definidos no firmware recompilado, no fastboot e nos scripts distribuídos. Não renomeie essas pastas depois da instalação.

## Compilar

A compilação requer o toolchain MIPS `mipsel-mti-elf`, o SDK HCRTOS e as dependências indicadas no Makefile. Dentro desta árvore, execute:

```bash
cd source/CajuOS-GB300-v4.1
make doctor
make deps
make check
```

Para executar a verificação rápida do frontend, JS2300, boot logo e smoke tests dos cores:

```bash
make quick-check
```

O pacote SD intermediário do build usa diretórios sem espaços para evitar ambiguidades no Makefile. O alvo de distribuição converte esse estágio para os nomes públicos:

```bash
make sd-zip
```

O ZIP produzido por esse alvo contém `Caju OS/` e `Caju OS Data/` na raiz. O script de release do repositório também acrescenta idioma, configurações, diagnósticos, manifestos e o tutorial destinado ao usuário final.

## Funcionalidades de desempenho

O frontend nativo abre um menu antes do lançamento da ROM. Esse menu permite escolher `Compatibility`, `Balanced`, `Performance` ou `Ultra`, além de CPU, GPU/GE, frameskip, áudio e `Skip duplicate frames`. O Performance Manager aplica opções compatíveis aos cores Libretro e o apresentador pode descartar frames duplicados usando uma assinatura amostrada do framebuffer.

## Limitações

A compilação e os testes host não substituem a validação em um GB300 físico. Boot, LCD, botões, áudio, clocks, FPS, consumo e compatibilidade de cartão precisam ser confirmados com um cartão SD real e com backup integral do cartão original.

Para o procedimento de instalação, consulte [`docs/INSTALL-CajuOS-GB300.md`](../docs/INSTALL-CajuOS-GB300.md). Para a reprodução do pacote final, use [`scripts/build-cajuos-release.sh`](../scripts/build-cajuos-release.sh).
