# Checklist da release CajuOS GB300 v0.3.3-beta

## Conteúdo publicado

O repositório deve conter o README, changelog, relatório de auditoria e a pasta `overlay/` com o conteúdo exato do cartão. O arquivo `CajuOS-GB300-v0.3.3-beta-overlay.zip` deve ser anexado como asset da release.

## Avisos obrigatórios

A descrição deve dizer que o sistema é beta, específico para GB300, fornecido como overlay e ainda pendente de validação física. Deve recomendar backup integral e proibir gravação direta do ZIP com Rufus, Etcher ou `dd`.

## Tópicos

`gb300`, `cajuos`, `unifrog`, `frogos`, `retro-gaming`, `retro-handheld`, `emulation`, `firmware`, `mipsel`, `homebrew`, `playstation`, `snes`, `gba`, `megadrive`, `pc-engine`, `beta`

## Evidências

O firmware deve passar `sha256sum -c checksums/FIRMWARE-SHA256SUMS.txt`. O pacote ZIP deve passar `unzip -t`. A documentação deve distinguir seleção de CUE no driver virtual de execução real do QPSX no GB300.

## Não incluir

Não incluir ROMs comerciais, BIOS proprietárias, saves pessoais, tokens, credenciais, arquivos de configuração do usuário ou dumps capturados de hardware de terceiros.
