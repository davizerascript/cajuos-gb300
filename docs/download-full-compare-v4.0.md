# Comparação completa de download — CajuOS 4.0 x UniFrog v0.5.2

> A comparação é usada somente para conferir contratos de instalação e estrutura técnica. Arquivos adicionados pelo CajuOS são esperados; divergências no firmware, manifestos e configurações são parte da personalização do CajuOS.

| Categoria | Quantidade |
| --- | ---: |
| Arquivos somente no CajuOS | 16 |
| Arquivos somente na referência | 1 |
| Arquivos comuns com hash idêntico | 22 |
| Arquivos comuns com hash diferente | 12 |

## Somente no CajuOS

- `README-CAJUOS.txt`
- `REPRODUCE-CAJUOS.txt`
- `ROMS/.keep`
- `unifrog/.package.1556949901.stamp`
- `unifrog_data/cajuos-manifest.ini`
- `unifrog_data/cajuos/assets/boot-splash-320x240.png`
- `unifrog_data/cajuos/assets/welcome-splash-320x240.png`
- `unifrog_data/cajuos/diagnostics/cajuos_controls.c`
- `unifrog_data/cajuos/diagnostics/cajuos_controls.h`
- `unifrog_data/cajuos/diagnostics/test_cajuos_controls.c`
- `unifrog_data/controls-test.txt`
- `unifrog_data/languages/portugues.ini`
- `unifrog_data/scripts/cajuos-health-check.js`
- `unifrog_data/scripts/cajuos-snes-benchmark.js`
- `unifrog_data/scripts/cajuos-storage-safe.js`
- `unifrog_data/settings.ini`

## Somente na referência

- `unifrog/.package.835061016.stamp`

## Comuns alterados

- `unifrog/cores/fceumm.bin`
- `unifrog/cores/gambatte.bin`
- `unifrog/cores/gpsp-gbac-prosty.bin`
- `unifrog/cores/gpsp.bin`
- `unifrog/cores/pce-fast.bin`
- `unifrog/cores/picodrive.bin`
- `unifrog/cores/qpsx.bin`
- `unifrog/cores/quicknes.bin`
- `unifrog/cores/snes9x2005.bin`
- `unifrog/firmware/unifrog.bin`
- `unifrog/manifest.ini`
- `unifrog_data/scripts/frontend-driver/_fd-lib.js`

## Comuns idênticos

- `bios/bisrv.asd`
- `unifrog/LICENSE.txt`
- `unifrog/THIRD_PARTY.md`
- `unifrog/cores/gearboy.bin`
- `unifrog/cores/snes9x2002.bin`
- `unifrog_data/languages/deutsch.ini`
- `unifrog_data/languages/espanol.ini`
- `unifrog_data/languages/francais.ini`
- `unifrog_data/languages/italiano.ini`
- `unifrog_data/scripts/audio-test.js`
- `unifrog_data/scripts/display-benchmark.js`
- `unifrog_data/scripts/display-color-test.js`
- `unifrog_data/scripts/frontend-driver-core.js`
- `unifrog_data/scripts/frontend-driver-frontend.js`
- `unifrog_data/scripts/frontend-driver.js`
- `unifrog_data/scripts/frontend-driver/core-tests.js`
- `unifrog_data/scripts/frontend-driver/frontend-tests.js`
- `unifrog_data/scripts/frontend-driver/storage-stress-tests.js`
- `unifrog_data/scripts/storage-interference-probe.js`
- `unifrog_data/scripts/storage-quick-benchmark.js`
- `unifrog_data/scripts/storage-stress-aggressive.js`
- `unifrog_data/scripts/storage-stress-sweep.js`

## Conclusão

O resultado deve ser lido junto com `download-audit-v4.0.md`: o CajuOS precisa manter os caminhos técnicos esperados pelo boot, mas não precisa ter os mesmos hashes do pacote de referência em firmware, manifestos, configurações, idiomas, scripts ou diagnósticos.
