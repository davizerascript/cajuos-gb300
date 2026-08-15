# Relatório técnico de testes — CajuOS GB300 4.0

**Projeto:** CajuOS GB300
**Versão:** 4.0
**Branch de validação:** `fix/cajuos-independent-v4`
**Data da rodada:** 15 de agosto de 2026
**Responsável pelo relatório:** **Manus AI**

## 1. Objetivo e escopo

Esta rodada tratou o CajuOS GB300 4.0 como um download novo e verificou a cadeia de distribuição, a árvore de código, os testes automatizados do firmware e a execução de ROMs em cores Libretro equivalentes no host. O objetivo principal foi confirmar que o pacote SD pode ser extraído diretamente na raiz do cartão, que a nova árvore fonte está identificada como CajuOS e que as funções de desempenho continuam presentes após a renomeação e a limpeza de identidade do projeto [1].

A comparação com o pacote UniFrog v0.5.2 foi utilizada somente para verificar contratos técnicos de compatibilidade do GB300 — caminhos esperados, conjunto de cores e arquivos necessários ao boot. Ela **não** é usada para definir a identidade do projeto: o CajuOS é distribuído como projeto independente, enquanto os nomes internos `unifrog/` e `unifrog_data/` permanecem por compatibilidade com o runtime proprietário do aparelho.

## 2. Funcionalidades incluídas no CajuOS 4.0

O fluxo nativo agora abre um menu pré-jogo após a seleção da ROM e do core. A implementação está em `src/native_frontend.c` e utiliza a visão `FRONTEND_VIEW_PRELAUNCH`. O usuário pode iniciar o jogo ou ajustar os parâmetros de desempenho antes do lançamento.

| Grupo | Opções entregues | Implementação principal |
| --- | --- | --- |
| Inicialização | `Start game` e `Back` | Menu pré-jogo do frontend nativo |
| Perfil de desempenho | `Compatibility`, `Balanced`, `Performance` e `Ultra` | Performance Manager do host Libretro |
| Vídeo e apresentação | CPU, GPU/GE, filtros, renderer, sincronização e apresentação | Aplicação centralizada de opções por perfil |
| Fluidez | Frameskip e `Skip duplicate frames` | Configuração de core e assinatura amostrada do framebuffer |
| Áudio | Controle de modo e prioridade de áudio por perfil | Opções do host e dos cores |
| Persistência | Perfil padrão e `skip_duplicate_frames` em `settings.ini` | `overlay/unifrog_data/settings.ini` |

O Performance Manager aplica automaticamente as opções compatíveis do core depois do carregamento do arquivo de opções. O recurso de frames duplicados calcula uma assinatura amostrada do framebuffer e evita reapresentar imagens idênticas quando a opção está habilitada. Como essas opções dependem das capacidades de cada core, o resultado esperado é uma política de melhor esforço: o perfil é aplicado quando o core expõe a opção correspondente, e as demais configurações permanecem inalteradas.

## 3. Verificação de build e qualidade do firmware

A árvore de código validada foi `source/CajuOS-GB300-v4.0`. Os testes foram executados dentro dela, com o toolchain MIPS instalado em `/opt/mipsel-mti-elf` e os SDKs e dependências já resolvidos no ambiente.

| Verificação | Comando | Resultado |
| --- | --- | --- |
| Higiene do repositório, doctor, smoke dos cores, frontend nativo, JS2300 e boot logo | `make quick-check` | **PASS**, código de saída 0 |
| SDK, ASD, pacote SD, firmware, manifesto, binários dos cores e layout de memória | `make check` | **PASS**, código de saída 0 |
| Sintaxe do diagnóstico de saúde | `node --check overlay/unifrog_data/scripts/cajuos-health-check.js` | **PASS** |
| Sintaxe do benchmark SNES | `node --check overlay/unifrog_data/scripts/cajuos-snes-benchmark.js` | **PASS** |
| Sintaxe da biblioteca do frontend driver | `node --check overlay/unifrog_data/scripts/frontend-driver/_fd-lib.js` | **PASS** |
| Cores MIPS empacotados | 11 módulos `.bin` obrigatórios | **PASS** |
| Fastboot | `fastboot.asd` com validação de tamanho, payload e CRC | **PASS** |
| Layout de memória | Checagem de `_ebss` e seções `NOBITS` nos executáveis | **PASS** |

Os warnings de `make` relacionados a `-j6` são avisos do jobserver, não falhas de compilação. A execução do `make check` terminou com código 0 depois de validar os artefatos, e o `make quick-check` terminou com código 0 após imprimir `OK` para cada subetapa.

## 4. Auditoria do pacote SD como download novo

O arquivo `release/CajuOS-GB300-v4.0-sdcard.zip` foi analisado em diretório temporário vazio, sem confiar no estado da árvore de trabalho. A auditoria confirmou que o conteúdo é instalável diretamente na raiz do cartão SD e que não existe uma pasta intermediária envolvendo todo o sistema [2].

| Critério | Resultado |
| --- | --- |
| Layout na raiz do ZIP | **PASS** |
| Ausência de caminhos inseguros | **PASS** |
| Ausência de entradas duplicadas | **PASS** |
| Ausência de pasta intermediária de instalação | **PASS** |
| Caminhos essenciais presentes | **PASS** |
| Conjunto de cores igual ao da referência técnica | **PASS** |
| `unifrog/firmware/unifrog.bin` | **PASS** |
| `unifrog/manifest.ini` | **PASS** |
| `unifrog_data/settings.ini` | **PASS** |
| `unifrog_data/scripts/frontend-driver.js` | **PASS** |
| `unifrog_data/scripts/frontend-driver/_fd-lib.js` | **PASS** |
| `ROMS/.keep` e `bios/bisrv.asd` | **PASS** |

O pacote SD possui os seguintes 11 cores: `fceumm`, `gambatte`, `gearboy`, `gpsp`, `gpsp-gbac-prosty`, `pce-fast`, `picodrive`, `qpsx`, `quicknes`, `snes9x2002` e `snes9x2005`. O hash SHA-256 do arquivo é `6893d54ad8966ca81b8f72973c331dd12461fb689894bc019bd51fef77510e3f` [4].

## 5. Auditoria do pacote fonte

O pacote fonte foi regenerado depois da renomeação para `source/CajuOS-GB300-v4.0`. Durante a validação, foi identificado que uma compactação ingênua incluiria dependências baixadas, objetos, mapas, outputs MIPS e metadados Git. O asset público foi corrigido para conter somente a árvore fonte reproduzível, preservando os arquivos `.gitmodules` e removendo diretórios `build`, `output`, `.deps`, metadados `.git` e artefatos temporários.

| Critério | Resultado |
| --- | --- |
| Extração em diretório temporário | **PASS** |
| `Makefile` presente | **PASS** |
| Frontend nativo presente | **PASS** |
| Host Libretro presente | **PASS** |
| Ausência de `build/`, `output/` e `.deps/` | **PASS** |
| Ausência de metadados `.git` | **PASS** |
| Tamanho do pacote fonte limpo | aproximadamente 23 MB |
| SHA-256 | `2c11f56e433cc782498c7bfde457bd729a3ea92fccebe7ed30ef7c79604b2843` |

O pacote fonte está em `release/CajuOS-GB300-source-v4.0.zip`, com checksum publicado em `release/CAJUOS-SOURCE-SHA256SUMS.txt` [5].

## 6. Execução de ROMs no host

Os testes de ROM no host não substituem o teste no GB300 físico, mas confirmam que os arquivos de conteúdo são reconhecidos e que os cores Libretro correspondentes conseguem inicializar o conteúdo em um frontend separado. O RetroArch foi executado com drivers de vídeo, áudio e entrada nulos para evitar dependência de uma sessão gráfica.

| Plataforma | ROM e core | Procedimento | Resultado |
| --- | --- | --- | --- |
| GBA | `240pee_mb.gba`, mGBA Libretro | RetroArch, 60 frames, vídeo/áudio/entrada nulos | **PASS**; o log registra carregamento do conteúdo, geometria GBA de 240×160 e encerramento normal |
| SNES | `inidisp_brightness_0.sfc`, Snes9x Libretro | ROM compilada localmente pelo assembler BASS e executada no RetroArch | **PASS parcial**; checksum LoROM reconhecido, geometria 256×224 e execução iniciada; o processo headless não respeitou o encerramento automático e foi interrompido pelo ambiente |

A ROM SNES de teste foi compilada a partir de `snes-test-roms/src/hardware-tests/inidisp_brightness_0.asm`. O Snes9x identificou o título `INIDISP BRIGHTNESS 0`, informou `checksum ok`, modo LoROM, 1 Mbit, NTSC e taxa de 60,10 FPS. Isso valida carregamento e inicialização do core no host, mas não deve ser apresentado como medição de desempenho do GB300.

O teste GBA confirma a execução host de uma ROM homebrew real. Ele também produziu um arquivo SRAM no diretório do RetroArch, sem erro de carregamento do core ou do conteúdo. Não foi possível observar visualmente o menu pré-jogo do CajuOS nesse teste porque os cores host não executam o frontend nativo MIPS do GB300; a presença do menu foi validada por build, inspeção de símbolos/fontes e smoke tests do frontend.

## 7. Comparação técnica com a referência

A comparação completa dos ZIPs confirmou 16 arquivos somente no CajuOS, 1 arquivo somente na referência, 22 arquivos comuns idênticos e 12 arquivos comuns com hash diferente [3]. As diferenças são esperadas para uma distribuição independente: incluem manifesto, firmware recompilado, cores recompilados, configurações, idioma português, diagnósticos e scripts do CajuOS.

| Categoria | Quantidade | Interpretação |
| --- | ---: | --- |
| Somente no CajuOS | 16 | Personalizações e ferramentas novas da distribuição |
| Somente na referência | 1 | Stamp interno do pacote de referência |
| Comuns idênticos | 22 | Contratos e arquivos preservados |
| Comuns alterados | 12 | Firmware, cores e componentes personalizados |
| Conjunto de cores | 11 contra 11 | Compatibilidade de catálogo preservada |

A conclusão técnica é que o CajuOS mantém os caminhos internos exigidos pelo boot do aparelho, mas possui identidade, manifesto, documentação e recursos próprios. O uso dos nomes `unifrog/` e `unifrog_data/` é uma decisão de compatibilidade de runtime, não uma declaração de origem do projeto.

## 8. Limitações e validações pendentes no hardware real

O ambiente disponível não contém um GB300 físico conectado. Portanto, esta rodada não consegue confirmar boot efetivo no SoC HCSEMI B210, imagem no LCD de 320×240, leitura dos botões, áudio no DAC, clocks reais, FPS medido, comportamento térmico, consumo de bateria ou interação manual com o menu pré-jogo. A auditoria de ZIP também não pretende validar esses itens [2].

A etapa recomendada antes de considerar a versão completamente validada em campo é extrair `CajuOS-GB300-v4.0-sdcard.zip` na raiz de um cartão SD, iniciar o GB300, abrir uma ROM para cada família importante e confirmar visualmente o menu `Performance`. Em seguida, devem ser comparados `Compatibility`, `Balanced`, `Performance` e `Ultra`, além de `Frameskip` e `Skip duplicate frames`, com atenção especial a SNES, GBA e PCE, que são os casos mais sensíveis ao orçamento de CPU e memória.

## 9. Artefatos da versão

| Artefato | Local | SHA-256 |
| --- | --- | --- |
| Pacote instalável no cartão SD | `release/CajuOS-GB300-v4.0-sdcard.zip` | `6893d54ad8966ca81b8f72973c331dd12461fb689894bc019bd51fef77510e3f` |
| Pacote fonte limpo | `release/CajuOS-GB300-source-v4.0.zip` | `2c11f56e433cc782498c7bfde457bd729a3ea92fccebe7ed30ef7c79604b2843` |
| Checksums do SD | `release/CAJUOS-SDCARD-SHA256SUMS.txt` | checksum do arquivo de checksums versionado |
| Checksums da fonte | `release/CAJUOS-SOURCE-SHA256SUMS.txt` | checksum do arquivo de checksums versionado |

## Referências

[1]: `RELEASE-NOTES-v4.0.md` — notas oficiais da versão CajuOS GB300 4.0.

[2]: `download-audit-v4.0.md` — auditoria de download limpo e contratos de instalação.

[3]: `download-full-compare-v4.0.md` — comparação completa de hashes entre CajuOS e a referência técnica.

[4]: `../release/CAJUOS-SDCARD-SHA256SUMS.txt` — checksum do pacote instalável no cartão SD.

[5]: `../release/CAJUOS-SOURCE-SHA256SUMS.txt` — checksum do pacote fonte limpo.
