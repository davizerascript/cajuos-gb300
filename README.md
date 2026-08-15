# CajuOS GB300

**CajuOS GB300 v0.3.3-beta** é uma distribuição experimental em formato de **overlay para cartão SD** do console portátil **GB300**. O projeto é baseado no ecossistema [UniFrog v0.5.2](https://github.com/axgdev/UniFrog) e adiciona uma camada de configuração, interface, diagnóstico e ajustes voltados ao GB300.

**Autor/mantenedor:** [@melo._.071 no Instagram](https://www.instagram.com/melo._.071/)

> **Estado do projeto: BETA.** Esta versão foi verificada estruturalmente e em cartão virtual, mas ainda não foi validada em um GB300 físico pelo mantenedor desta publicação. Ela pode conter erros de boot, vídeo, áudio, controles, desempenho, compatibilidade de cartão ou recuperação. Use somente com backup integral do cartão original. Leia também o [aviso detalhado de beta](BETA-NOTICE.md) antes de instalar.

## Compatibilidade

O pacote foi preparado para o **console GB300**, com atenção à organização de cartão FAT32, variantes de hardware e fluxo nativo do UniFrog. A compatibilidade exata entre GB300 v1, GB300 v2, unidades com tela IPS modificada e revisões de bootloader ainda depende de teste no hardware correspondente.

Não use este ZIP em SF2000, TrimUI ou outro console. Não grave o ZIP como imagem com Rufus, Etcher ou `dd`: ele é um overlay de arquivos, não uma imagem de disco.

## O que há de novo em relação ao FrogOS/UniFrog base

| Área | CajuOS GB300 v0.3.3-beta | FrogOS/UniFrog base |
| --- | --- | --- |
| Base técnica | UniFrog v0.5.2 com firmware CajuOS recompilado | Distribuição mais conservadora da base UniFrog |
| Público-alvo | GB300, com foco no fluxo e na documentação para este console | Uso geral conforme o pacote upstream |
| Interface | Tema CajuOS, splash de boot, splash de boas-vindas e layout vertical de sistemas | Interface mais enxuta, sem a personalização CajuOS |
| Idioma | Português incluído, além dos idiomas distribuídos pelo pacote | Sem a camada de localização CajuOS no pacote comparado |
| SNES | `snes9x2002` como padrão e `snes9x2005` como fallback | O core pode estar presente, mas a seleção explícita depende do frontend/base |
| PS1 | QPSX com driver que prioriza `.cue` quando coexistem `.cue` e `.bin` | Priorização CUE não presente no driver original comparado |
| Diagnóstico | Health-check, driver de testes, benchmark SNES e testes de armazenamento | Menos diagnósticos e personalização no overlay comparado |
| Segurança de distribuição | README de overlay, checksums de firmware e instruções de backup | Pacote mais simples, porém com menos documentação local |
| Desempenho | `cpu=918`, áudio ligado, `frameskip=1` e perfil de SD conservador | Desempenho real depende do perfil e da versão do frontend |

A comparação não permite afirmar que o CajuOS é mais rápido. O CajuOS possui hipóteses e instrumentação mais específicas para SNES/GB300, mas FPS, frame time, latência, autonomia e áudio ainda precisam ser medidos no console físico. Para uso conservador, FrogOS continua sendo a referência de menor risco de release; o CajuOS é uma alternativa experimental com mais personalização e ambição de produto.

## CajuOS 4.0 — Performance Manager

A versão CajuOS 4.0 adiciona um menu nativo antes do lançamento de cada jogo. Depois de escolher a ROM, a pessoa pode selecionar o perfil de desempenho, CPU, GPU/GE, frameskip, áudio e descarte de frames repetidos. O CajuOS possui sua própria árvore de firmware, frontend, cores, configurações e ferramentas; referências técnicas a outros projetos são apenas compatibilidade histórica e não definem a identidade do CajuOS.

O repositório publica o [source/build independente do CajuOS](source/README.md), o [pacote fonte ZIP](release/CajuOS-GB300-source-v4.0.zip), o script [`scripts/build-cajuos-release.sh`](scripts/build-cajuos-release.sh) e o [ZIP pronto para cartão SD](release/CajuOS-GB300-v4.0-sdcard.zip). As notas detalhadas estão em [`docs/RELEASE-NOTES-v4.0.md`](docs/RELEASE-NOTES-v4.0.md).

## Correção de PS1 nesta versão

O driver `unifrog_data/scripts/frontend-driver/_fd-lib.js` agora mantém um fallback geral de extensão e, para o core `qpsx`, prioriza arquivos `.cue` quando há mais de um arquivo compatível na pasta. O teste virtual com uma imagem PS1 homebrew selecionou:

```text
RUN qpsx core=qpsx ... rom=/media/mmcblk0/ROMS/PS/compilation.cue
```

Para jogos PS1 em formato BIN/CUE, mantenha o `.cue` e todos os arquivos referenciados por ele na mesma pasta. A correção garante a seleção do CUE no driver; ela não substitui o teste físico do QPSX, nem garante compatibilidade de cada imagem, BIOS ou jogo.

## Estrutura esperada no cartão

Extraia o conteúdo do pacote na raiz de uma cópia do cartão GB300 que já inicia corretamente:

```text
ROMS/
 bios/bisrv.asd
 unifrog/firmware/unifrog.bin
 unifrog/cores/*.bin
 unifrog_data/settings.ini
 unifrog_data/cajuos-manifest.ini
```

Preserve as ROMs, saves, BIOS pessoais e arquivos específicos do cartão original. Para PS1, use uma estrutura como:

```text
ROMS/PS/meu_jogo.cue
ROMS/PS/meu_jogo.bin
ROMS/SAVE/PSX/
```

O CajuOS não distribui ROMs comerciais, BIOS proprietárias ou jogos. Os testes deste projeto usaram uma ROM GBA fornecida pelo usuário e demos/homebrew autorizados separadamente.

## Instalação segura

1. Faça uma imagem integral do cartão original antes de modificar qualquer arquivo.
2. Confirme se o console é um GB300 compatível e se o cartão está em FAT32.
3. Desligue o console, remova o cartão com segurança e extraia o overlay na raiz da cópia.
4. Preserve `ROMS/`, saves e BIOS do cartão original.
5. Ejete o cartão corretamente e faça o primeiro boot sem alterar CPU, frameskip, perfil UHS, BIOS ou áudio.
6. Teste primeiro boot, menu, controles e uma ROM simples. Só depois teste SNES, Genesis, PCE, GBA e PS1.

Se ocorrer tela preta antes do menu, reinício, travamento no logo ou perda de controles, desligue e restaure a imagem original. Não tente corrigir uma tela preta alterando parâmetros de desempenho.

## Verificações desta release

| Verificação | Resultado |
| --- | --- |
| ZIP íntegro | PASS |
| `sha256sum -c checksums/FIRMWARE-SHA256SUMS.txt` | PASS |
| JavaScript com `node --check` | PASS |
| Cabeçalhos OCFU de 11 cores | PASS |
| Compilação estrita do módulo de controles | PASS |
| GCC analyzer | PASS |
| Testes ASan/UBSan do módulo de controles | PASS |
| Health-check em cartão virtual | PASS, 8/8 |
| Driver frontend/core em cartão virtual | PASS |
| Seleção de `.cue` para QPSX em cartão virtual | PASS |
| Boot, tela, áudio, controles e autonomia no GB300 físico | **PENDENTE** |

Estas verificações não equivalem a um boot físico. Os binários MIPS, cores OCFU, LCD, keypad, áudio, MMIO e controlador SD proprietários não foram executados integralmente no hardware-alvo durante a auditoria.

## Arquivos da release

O artefato principal é `CajuOS-GB300-v0.3.3-beta-overlay.zip`. Ele contém somente o overlay do sistema e não contém ROMs comerciais. O manifesto de firmware está em `checksums/FIRMWARE-SHA256SUMS.txt`; o relatório técnico detalhado está em `docs/CajuOS-v0.3.3-beta-audit.md`.

A reprodução completa da build não está incluída neste overlay executável. O pacote documenta os commits e o checksum do firmware, mas source, patch e toolchain devem ser publicados separadamente quando estiverem prontos.

## Licença e componentes de terceiros

Consulte `unifrog/LICENSE.txt` e `unifrog/THIRD_PARTY.md`. Os cores possuem licenças distintas; a distribuição e eventual redistribuição devem respeitar os avisos de cada componente.

## Feedback e relatórios de erro

Ao relatar um problema, informe a variante do console, revisão de tela, capacidade/marca do cartão, se o cartão original ainda inicia, o sintoma exato e, quando possível, os arquivos de log de `unifrog_data/logs/`. Não publique BIOS proprietárias, ROMs comerciais ou saves pessoais em issues públicas.

## Referências

- [GB300 — hardware e firmware](https://github.com/nummacway/gb300)
- [UniFrog](https://github.com/axgdev/UniFrog)
- [Tag UniFrog v0.5.2](https://github.com/axgdev/UniFrog/tree/v0.5.2)
- [240p Test Suite — homebrew usado em testes host](https://github.com/ArtemioUrbina/240pTestSuite)

## Tópicos sugeridos para o GitHub

`gb300`, `cajuos`, `unifrog`, `frogos`, `retro-gaming`, `retro-handheld`, `emulation`, `firmware`, `mipsel`, `homebrew`, `playstation`, `snes`, `gba`, `megadrive`, `pc-engine`, `beta`
