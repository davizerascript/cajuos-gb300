# Relatório técnico de testes — CajuOS GB300 4.1

## Escopo

Esta versão altera os nomes públicos usados no cartão SD para `Caju OS/` e `Caju OS Data/`. A mudança foi aplicada no firmware HCRTOS/MIPS, no fastboot, no frontend nativo, no host Libretro, no runtime JS2300, nos scripts de diagnóstico, no Makefile e no empacotador. O arquivo público do firmware passou a ser `Caju OS/firmware/cajuos.bin`.

A árvore validada foi `source/CajuOS-GB300-v4.1`. A implementação continua independente e mantém somente os identificadores internos de compilação necessários para a ABI e para os headers do firmware.

## Testes executados

| Teste | Resultado | Observação |
| --- | --- | --- |
| `sh -n scripts/build-cajuos-release.sh` | **PASS** | Empacotador v4.1 válido |
| `python3 -m py_compile` dos scripts de auditoria | **PASS** | Auditoria Python válida |
| `node --check` dos scripts principais | **PASS** | Health-check, benchmark SNES e frontend-driver |
| `make check` | **PASS** | Rebuild limpo depois da renomeação da árvore |
| `make quick-check` | **PASS** | Smoke tests do frontend, JS2300, boot logo e cores |
| `make sd-zip` | **PASS** | ZIP intermediário contém `Caju OS/` e `Caju OS Data/` |
| `make install SDCARD=<diretório temporário>` | **PASS** | Caminhos com espaços criados corretamente |
| `unzip -t` do ZIP SD | **PASS** | Nenhum erro de compressão |
| `unzip -t` do ZIP fonte | **PASS** | Nenhum erro de compressão |
| Auditoria de download novo | **PASS** | Raiz, segurança, caminhos essenciais e 11 cores |
| Busca por diretórios antigos no ZIP | **PASS** | Nenhum `unifrog/`, `unifrog_data/` ou `unifrog.bin` |

## Auditoria do pacote SD

O pacote foi extraído logicamente como um download novo e apresentou exatamente os diretórios públicos esperados na raiz:

```text
Caju OS/
Caju OS Data/
ROMS/
bios/
```

A auditoria confirmou que não existe pasta intermediária, não há caminhos inseguros ou entradas duplicadas, todos os caminhos essenciais estão presentes e o conjunto de cores é igual ao da referência técnica, com onze cores em cada conjunto.

O comparador registrou 49 arquivos somente no CajuOS, 34 somente na referência técnica, 1 arquivo comum com hash idêntico e nenhum arquivo comum com hash diferente. A diferença de contagem é esperada porque o novo layout usa nomes públicos próprios e porque a release contém o tutorial, manifestos e recursos de distribuição do CajuOS.

## Artefatos finais

| Artefato | SHA-256 |
| --- | --- |
| `release/CajuOS-GB300-v4.1-sdcard.zip` | `d82e0c1fee401d49637945c26a1d7c7d366a3fe0295abc836051cdd2ab53d8b1` |
| `release/CajuOS-GB300-source-v4.1.zip` | `68c2e512d2cab9e0df0390502c359e62302b9458f6f6b6789c9a673d7233b0af` |

O pacote fonte foi compactado sem `build/`, `output/`, `.deps`, objetos, mapas, arquivos de dependência ou metadados Git. O arquivo fonte contém a árvore `source/CajuOS-GB300-v4.1` e preserva os `.gitmodules` necessários para reprodução.

## Instalação documentada

O tutorial para usuários está em [`INSTALL-CajuOS-GB300.md`](INSTALL-CajuOS-GB300.md) e também foi resumido em `README-CAJUOS.txt`, dentro do pacote SD. As instruções explicam que o ZIP deve ser extraído diretamente na raiz de uma cópia do cartão, que o pacote fonte não serve para instalação e que as ROMs devem ser copiadas separadamente para `ROMS/`.

O primeiro boot recomendado usa o perfil `Balanced`. Depois da confirmação de boot, imagem, controles e áudio, a pessoa pode testar `Compatibility`, `Performance` e `Ultra` individualmente.

## Limitação física

Os testes confirmam a coerência do firmware recompilado, do empacotamento e dos caminhos públicos. Eles não substituem o teste em um GB300 físico. Ainda precisam ser confirmados em hardware real o bootloader da revisão específica, LCD, botões, áudio, clocks CPU/GE, FPS, consumo, estabilidade térmica e compatibilidade de cada cartão SD.
