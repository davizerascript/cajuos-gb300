# Auditoria de download limpo — CajuOS

> O ZIP CajuOS foi tratado como um arquivo recém-baixado e comparado com um ZIP de referência técnica apenas para validar contratos de layout e componentes.

## Resultado

- CajuOS ZIP: `CajuOS-GB300-v4.1-sdcard.zip`; SHA-256 `d82e0c1fee401d49637945c26a1d7c7d366a3fe0295abc836051cdd2ab53d8b1`; 6363222 bytes.
- Referência: `Unifrog-sdcard-v0.5.2.zip`; SHA-256 `1cc66759bdb8b19cf5614de32f52dfd479731ae61bfe701c8c952c454382ce0b`; 6716565 bytes.
- Layout raiz correto: **PASS**.
- ZIP sem caminhos inseguros ou entradas duplicadas: **PASS**.
- Pasta intermediária para instalação: **PASS**.
- Caminhos essenciais presentes: **PASS**.
- Conjunto de cores igual ao da referência: **PASS**.

## Layout de instalação

| Item | Resultado |
| --- | --- |

| `Caju OS/` | presente |
| `Caju OS Data/` | presente |
| `README-CAJUOS.txt/` | presente |
| `REPRODUCE-CAJUOS.txt/` | presente |
| `ROMS/` | presente |
| `bios/` | presente |

## Caminhos essenciais

| Caminho | CajuOS | Referência |
| --- | --- | --- |

| `Caju OS/firmware/cajuos.bin` | PASS | ausente |
| `Caju OS/manifest.ini` | PASS | ausente |
| `Caju OS/LICENSE.txt` | PASS | ausente |
| `Caju OS/THIRD_PARTY.md` | PASS | ausente |
| `Caju OS Data/settings.ini` | PASS | ausente |
| `Caju OS Data/languages/portugues.ini` | PASS | ausente |
| `Caju OS Data/scripts/frontend-driver.js` | PASS | ausente |
| `Caju OS Data/scripts/frontend-driver/_fd-lib.js` | PASS | ausente |
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
    "Caju OS/firmware/cajuos.bin",
    "Caju OS/manifest.ini",
    "Caju OS/LICENSE.txt",
    "Caju OS/THIRD_PARTY.md",
    "Caju OS Data/settings.ini",
    "Caju OS Data/languages/portugues.ini",
    "Caju OS Data/scripts/frontend-driver.js",
    "Caju OS Data/scripts/frontend-driver/_fd-lib.js",
    "ROMS/.keep",
    "bios/bisrv.asd"
  ],
  "missing_required_in_caju": [],
  "missing_required_in_reference": [
    "Caju OS/firmware/cajuos.bin",
    "Caju OS/manifest.ini",
    "Caju OS/LICENSE.txt",
    "Caju OS/THIRD_PARTY.md",
    "Caju OS Data/settings.ini",
    "Caju OS Data/languages/portugues.ini",
    "Caju OS Data/scripts/frontend-driver.js",
    "Caju OS Data/scripts/frontend-driver/_fd-lib.js",
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
