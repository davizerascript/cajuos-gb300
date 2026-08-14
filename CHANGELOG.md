# Changelog — CajuOS GB300

## v0.3.3-beta

Esta versão corrige o fluxo de seleção de imagens de PlayStation 1 no driver do frontend. Quando há arquivos compatíveis concorrentes na pasta `ROMS/PS`, o core QPSX prioriza o arquivo `.cue`; para os demais cores, o comportamento geral de fallback por extensão é preservado.

A release também atualiza os manifestos para `0.3.3`, registra `firmware_dirty=0`, inclui o checksum direto do firmware e mantém o pacote como overlay seguro para cartão, sem ROMs comerciais ou BIOS proprietária.

Foram repetidas as validações de integridade do ZIP, checksum, sintaxe JavaScript, cabeçalhos OCFU, compilação estrita, GCC analyzer e sanitizers do módulo de controles. O cartão virtual passou health-check, frontend-driver, benchmark SNES e seleção de CUE no QPSX.

### Limitações conhecidas

O boot físico no GB300 continua pendente. Ainda não foram confirmados em hardware LCD, keypad, áudio, FPS, latência, autonomia, estabilidade elétrica, compatibilidade com todas as revisões v1/v2 ou comportamento de QPSX com BIOS e imagens PS1 específicas.

A reprodução completa da build não está dentro do overlay executável. O release documenta commits e hashes, mas source, patch e toolchain devem acompanhar uma distribuição de desenvolvimento separada.

## v0.3.2-beta

Incluiu benchmark SNES com áudio e frameskip explícitos, checksums diretos, documentação de reprodução e correções de empacotamento. O driver PS1 ainda podia selecionar um `.bin` antes de um `.cue` quando ambos coexistiam.

## v0.3.1-beta

Corrigiu layout de overlay, versão de release, referências de assets e consistência de metadata. O pacote ainda exigia validação de benchmark no hardware GB300.

## v0.2

Primeira revisão auditada do pacote executável CajuOS. A auditoria encontrou inconsistências entre o instalador/verificador e o layout real do ZIP, que foram corrigidas nas revisões seguintes.
