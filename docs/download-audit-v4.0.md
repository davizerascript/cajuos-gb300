# Auditoria de download limpo — CajuOS 4.0

> O ZIP CajuOS foi tratado como um arquivo recém-baixado, extraído em uma pasta vazia e comparado com o ZIP UniFrog de referência apenas para validar contratos técnicos de layout e componentes.

## Resultado

- CajuOS ZIP: `CajuOS-GB300-v4.0-sdcard.zip`; SHA-256 `6893d54ad8966ca81b8f72973c331dd12461fb689894bc019bd51fef77510e3f`; 6363891 bytes.
- Referência: `Unifrog-sdcard-v0.5.2.zip`; SHA-256 `1cc66759bdb8b19cf5614de32f52dfd479731ae61bfe701c8c952c454382ce0b`; 6716565 bytes.
- Layout raiz correto: **PASS**.
- ZIP sem caminhos inseguros ou entradas duplicadas: **PASS**.
- Pasta intermediária para instalação: **PASS**.
- Caminhos essenciais presentes: **PASS**.
- Conjunto de cores igual ao da referência: **PASS**.

## Layout de instalação

| Item | Resultado |
| --- | --- |

| `README-CAJUOS.txt/` | presente |
| `REPRODUCE-CAJUOS.txt/` | presente |
| `ROMS/` | presente |
| `bios/` | presente |
| `unifrog/` | presente |
| `unifrog_data/` | presente |

## Caminhos essenciais

| Caminho | CajuOS | Referência |
| --- | --- | --- |

| `unifrog/firmware/unifrog.bin` | PASS | PASS |
| `unifrog/manifest.ini` | PASS | PASS |
| `unifrog/LICENSE.txt` | PASS | PASS |
| `unifrog/THIRD_PARTY.md` | PASS | PASS |
| `unifrog_data/settings.ini` | PASS | ausente |
| `unifrog_data/languages/portugues.ini` | PASS | ausente |
| `unifrog_data/scripts/frontend-driver.js` | PASS | PASS |
| `unifrog_data/scripts/frontend-driver/_fd-lib.js` | PASS | PASS |
| `ROMS/.keep` | PASS | ausente |
| `bios/bisrv.asd` | PASS | PASS |

## Cores

Cores no CajuOS: fceumm, gambatte, gearboy, gpsp, gpsp-gbac-prosty, pce-fast, picodrive, qpsx, quicknes, snes9x2002, snes9x2005.
Cores na referência: fceumm, gambatte, gearboy, gpsp, gpsp-gbac-prosty, pce-fast, picodrive, qpsx, quicknes, snes9x2002, snes9x2005.
Somente no CajuOS: nenhum.
Somente na referência: nenhum.

## JSON de auditoria

```json
{
  "required_paths": [
    "unifrog/firmware/unifrog.bin",
    "unifrog/manifest.ini",
    "unifrog/LICENSE.txt",
    "unifrog/THIRD_PARTY.md",
    "unifrog_data/settings.ini",
    "unifrog_data/languages/portugues.ini",
    "unifrog_data/scripts/frontend-driver.js",
    "unifrog_data/scripts/frontend-driver/_fd-lib.js",
    "ROMS/.keep",
    "bios/bisrv.asd"
  ],
  "missing_required_in_caju": [],
  "missing_required_in_reference": [
    "unifrog_data/settings.ini",
    "unifrog_data/languages/portugues.ini",
    "ROMS/.keep"
  ],
  "cores_only_in_caju": [],
  "cores_only_in_reference": [],
  "same_core_set": true,
  "nested_install_root_detected": false,
  "root_layout_ok": true,
  "zip_safe": true
}
```

## Limite do teste

Esta auditoria confirma o contrato de distribuição e os arquivos necessários para o runtime. Ela não consegue confirmar boot, LCD, áudio, controles, clocks ou FPS sem um GB300 físico.
