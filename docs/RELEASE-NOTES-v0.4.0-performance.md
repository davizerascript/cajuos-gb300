# CajuOS GB300 v0.4.0-performance

## Resumo

Esta versão consolida o CajuOS GB300 4.0 como um projeto independente e passa a publicar, no mesmo repositório, seu source editável, suas instruções de build e um ZIP de instalação para cartão SD.

## Menu pré-jogo

Depois de selecionar uma ROM e escolher o core compatível, o frontend nativo abre o menu `Launch`. O usuário pode iniciar o jogo ou ajustar o perfil sem entrar nas configurações gerais:

| Item | Valores |
|---|---|
| Performance | Compatibility, Balanced, Performance, Ultra |
| CPU | 198, 297, 396, 594, 702, 756, 810, 864 ou 918 MHz, conforme estabilidade do hardware |
| GPU | Perfil GE disponível no runtime |
| Frameskip | Off, Auto, Fixed 1 ou Fixed 2 |
| Audio | Enabled ou Muted |
| Duplicate frames | Present ou Skip |

A seleção é armazenada nas configurações do runtime. O botão `B` retorna para a seleção do core; `A` em `Start game` inicia a ROM.

## Performance Manager

O host libretro aplica os perfis às opções que cada core realmente registrar. Variáveis ausentes são ignoradas para evitar incompatibilidade. O perfil também habilita, quando suportado pelo core, renderer rápido, filtros de áudio reduzidos, transparência simplificada, limite de sprites conservador, frameskip interno e opções de overclock compatível.

O modo `Duplicate frames` calcula uma assinatura amostrada do framebuffer e não chama o presenter quando a imagem não mudou. Isso reduz cópias e trabalho do GE em menus, telas estáticas e frames repetidos. Ele não elimina o custo de emular a CPU e pode ser desativado se um jogo tiver animação sutil que não apareça nas amostras.

## Source e distribuição

A árvore `source/CajuOS-GB300-v4.0` contém o source do CajuOS, incluindo firmware, frontend, cores, host de emulação e ferramentas próprias. O Makefile baixa o SDK HCRTOS quando o repositório é obtido como ZIP e usa um mirror público do FFmpeg por padrão. Nomes internos de compatibilidade permanecem apenas onde o boot/runtime do aparelho exige esses contratos.

A release pronta é `release/CajuOS-GB300-v0.4.0-performance-sdcard.zip`. Ela é um overlay: extraia o conteúdo na raiz de uma cópia FAT32 do cartão original, preservando ROMs, saves e BIOS.

## Validação

Foram executados `make quick-check` e o build MIPS completo do CajuOS 4.0, incluindo doctor, core smoke, verificação do frontend, runtime JS2300, boot logo, link do firmware, conversão dos cores e geração do SD ZIP. O ZIP final passou em `unzip -t`, e o firmware foi verificado por SHA-256.

A validação física permanece pendente: o ambiente não possui um GB300 físico. Portanto, boot, tela, áudio, controles, clock real, estabilidade térmica, autonomia e compatibilidade de cada ROM ainda precisam ser confirmados no aparelho.
