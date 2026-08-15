# Comparação completa de download — CajuOS x referência técnica

> A comparação é usada somente para conferir contratos de instalação e estrutura técnica. Arquivos adicionados pelo CajuOS são esperados; divergências no firmware, manifestos e configurações são parte da personalização do CajuOS.

| Categoria | Quantidade |
| --- | ---: |
| Arquivos somente no CajuOS | 49 |
| Arquivos somente na referência | 34 |
| Arquivos comuns com hash idêntico | 1 |
| Arquivos comuns com hash diferente | 0 |

## Somente no CajuOS

- `Caju OS Data/cajuos-manifest.ini`
- `Caju OS Data/cajuos/assets/boot-splash-320x240.png`
- `Caju OS Data/cajuos/assets/welcome-splash-320x240.png`
- `Caju OS Data/cajuos/diagnostics/cajuos_controls.c`
- `Caju OS Data/cajuos/diagnostics/cajuos_controls.h`
- `Caju OS Data/cajuos/diagnostics/test_cajuos_controls.c`
- `Caju OS Data/controls-test.txt`
- `Caju OS Data/languages/deutsch.ini`
- `Caju OS Data/languages/espanol.ini`
- `Caju OS Data/languages/francais.ini`
- `Caju OS Data/languages/italiano.ini`
- `Caju OS Data/languages/portugues.ini`
- `Caju OS Data/scripts/audio-test.js`
- `Caju OS Data/scripts/cajuos-health-check.js`
- `Caju OS Data/scripts/cajuos-snes-benchmark.js`
- `Caju OS Data/scripts/cajuos-storage-safe.js`
- `Caju OS Data/scripts/display-benchmark.js`
- `Caju OS Data/scripts/display-color-test.js`
- `Caju OS Data/scripts/frontend-driver-core.js`
- `Caju OS Data/scripts/frontend-driver-frontend.js`
- `Caju OS Data/scripts/frontend-driver.js`
- `Caju OS Data/scripts/frontend-driver/_fd-lib.js`
- `Caju OS Data/scripts/frontend-driver/core-tests.js`
- `Caju OS Data/scripts/frontend-driver/frontend-tests.js`
- `Caju OS Data/scripts/frontend-driver/storage-stress-tests.js`
- `Caju OS Data/scripts/storage-interference-probe.js`
- `Caju OS Data/scripts/storage-quick-benchmark.js`
- `Caju OS Data/scripts/storage-stress-aggressive.js`
- `Caju OS Data/scripts/storage-stress-sweep.js`
- `Caju OS Data/settings.ini`
- `Caju OS/.package.2665594213.stamp`
- `Caju OS/LICENSE.txt`
- `Caju OS/THIRD_PARTY.md`
- `Caju OS/cores/fceumm.bin`
- `Caju OS/cores/gambatte.bin`
- `Caju OS/cores/gearboy.bin`
- `Caju OS/cores/gpsp-gbac-prosty.bin`
- `Caju OS/cores/gpsp.bin`
- `Caju OS/cores/pce-fast.bin`
- `Caju OS/cores/picodrive.bin`
- `Caju OS/cores/qpsx.bin`
- `Caju OS/cores/quicknes.bin`
- `Caju OS/cores/snes9x2002.bin`
- `Caju OS/cores/snes9x2005.bin`
- `Caju OS/firmware/cajuos.bin`
- `Caju OS/manifest.ini`
- `README-CAJUOS.txt`
- `REPRODUCE-CAJUOS.txt`
- `ROMS/.keep`

## Somente na referência

- `unifrog/.package.835061016.stamp`
- `unifrog/LICENSE.txt`
- `unifrog/THIRD_PARTY.md`
- `unifrog/cores/fceumm.bin`
- `unifrog/cores/gambatte.bin`
- `unifrog/cores/gearboy.bin`
- `unifrog/cores/gpsp-gbac-prosty.bin`
- `unifrog/cores/gpsp.bin`
- `unifrog/cores/pce-fast.bin`
- `unifrog/cores/picodrive.bin`
- `unifrog/cores/qpsx.bin`
- `unifrog/cores/quicknes.bin`
- `unifrog/cores/snes9x2002.bin`
- `unifrog/cores/snes9x2005.bin`
- `unifrog/firmware/unifrog.bin`
- `unifrog/manifest.ini`
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
- `unifrog_data/scripts/frontend-driver/_fd-lib.js`
- `unifrog_data/scripts/frontend-driver/core-tests.js`
- `unifrog_data/scripts/frontend-driver/frontend-tests.js`
- `unifrog_data/scripts/frontend-driver/storage-stress-tests.js`
- `unifrog_data/scripts/storage-interference-probe.js`
- `unifrog_data/scripts/storage-quick-benchmark.js`
- `unifrog_data/scripts/storage-stress-aggressive.js`
- `unifrog_data/scripts/storage-stress-sweep.js`

## Comuns alterados

- nenhum

## Comuns idênticos

- `bios/bisrv.asd`

## Conclusão

O resultado deve ser lido junto com o relatório de auditoria correspondente: o CajuOS precisa manter os caminhos técnicos definidos pelo próprio firmware e não precisa ter os mesmos hashes do pacote de referência técnica.
