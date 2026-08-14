# CajuOS GB300 v0.3.3-beta

## Resumo

Primeira release pública beta do CajuOS para o console portátil GB300. O download é um **overlay de cartão SD**, não uma imagem bruta. A versão é baseada no UniFrog v0.5.2 e adiciona tema CajuOS, português, diagnósticos, perfil SNES documentado e correção de seleção de imagens PS1.

**Autor/mantenedor:** [@melo._.071 no Instagram](https://www.instagram.com/melo._.071/)

## Correções e mudanças

- Corrige o driver QPSX para priorizar `.cue` quando `.cue` e `.bin` coexistem.
- Mantém `snes9x2002` como core SNES padrão e `snes9x2005` como fallback.
- Mantém perfil de armazenamento conservador e opções de áudio/frameskip documentadas.
- Inclui 11 cores OCFU: Gambatte, Gearboy, QuickNES, FCEUmm, Snes9x 2002, Snes9x 2005, PicoDrive, gpSP, gpSP GBAC+Prosty, PCE Fast e QPSX.
- Inclui tema CajuOS em 320×240, português e scripts JS2300 de diagnóstico.
- Registra `firmware_dirty=0`, commit de firmware e checksum verificável.

## Validação

- ZIP testado com `unzip -t`.
- Firmware conferido com `checksums/FIRMWARE-SHA256SUMS.txt`.
- JavaScript validado com `node --check`.
- OCFU validado em todos os 11 cores.
- Controles compilados com warnings estritos, GCC analyzer, ASan e UBSan.
- Health-check virtual: 8/8 passes, sem warnings.
- Driver virtual selecionou `ROMS/PS/compilation.cue` em cenário com `.cue` e `.bin`.
- Boot físico e desempenho no GB300 permanecem pendentes.

## Hashes

```text
ZIP
1776bb01a2c2d98b6bb1b27aa075292d44685bf601962a003a10170347036bd8  CajuOS-GB300-v0.3.3-beta-overlay.zip

FIRMWARE
904884a8a5ace55645367f0d62145b3403f83041d9f9f96775f592512dddf77a  unifrog/firmware/unifrog.bin
```

## Aviso importante

Este é um **beta exclusivo para GB300**. O mantenedor não possui um GB300 físico neste momento; portanto, a release não deve ser tratada como confirmação de boot, desempenho, áudio, controles, autonomia ou compatibilidade total. Faça backup integral do cartão original, use uma cópia e restaure o backup se houver tela preta ou falha de boot. Não use o ZIP em outro console e não o grave diretamente como imagem de disco.

Leia `BETA-NOTICE.md` e `docs/CajuOS-v0.3.3-beta-audit.md` antes da instalação.

## FrogOS/UniFrog

FrogOS/UniFrog continua sendo a referência conservadora e pública. O CajuOS não promete ser mais rápido: sua diferença está na personalização para GB300, localização em português, tema Caju, instrumentação de diagnóstico, perfil SNES explícito e prioridade CUE no PS1. Métricas reais de FPS, latência e autonomia aguardam teste físico.

## Source e componentes

A base UniFrog v0.5.2 é pública. O overlay beta distribui binários e metadata; o source/patch completo específico da build CajuOS ainda não acompanha este artefato. Consulte `overlay/unifrog/THIRD_PARTY.md`, `NOTICE-THIRD-PARTY.md` e os avisos de cada core antes de redistribuir componentes.

## Tópicos

`gb300` `cajuos` `unifrog` `frogos` `retro-gaming` `retro-handheld` `emulation` `firmware` `mipsel` `homebrew` `playstation` `snes` `gba` `megadrive` `pc-engine` `beta`

## English summary

CajuOS GB300 v0.3.3-beta is an experimental SD-card overlay for the DataFrog GB300. It is based on UniFrog v0.5.2, adds a Portuguese CajuOS interface and diagnostics, and fixes QPSX file selection by preferring `.cue` over `.bin` when both are present. It has passed structural and virtual-card checks, but it has **not been boot-tested on a physical GB300**. Back up the original card, use a copy, and do not install it on other consoles.
