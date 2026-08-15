# Auditoria técnica — CajuOS GB300 v0.3.3-beta

**Data:** 14 de agosto de 2026  
**Escopo:** revisão do pacote `CajuOS-GB300-executable-v0.3(4).zip`, comparação com CajuOS v0.3.2, FrogOS/UniFrog v0.5.2 e validação em cartão virtual.

## Veredito

A revisão v0.3.3-beta está **aprovada para teste físico controlado**, não para distribuição como release final garantidamente estável. O pacote agora apresenta overlay coerente, firmware com `firmware_dirty=0`, checksum verificável, todos os cores com cabeçalho OCFU válido e uma correção funcional no driver PS1: o QPSX prioriza `.cue` quando `.cue` e `.bin` coexistem na mesma pasta.

O teste não pode afirmar que o GB300 fará boot, porque o hardware não estava disponível. LCD, keypad, áudio, controlador SD, bootloader, clock real, consumo e estabilidade elétrica permanecem pendentes.

## Correção PS1 verificada

A alteração entre v0.3.2 e v0.3.3 está concentrada no `findRom()` do `frontend-driver/_fd-lib.js`. Antes, a primeira extensão compatível retornada por `fs.list()` podia ser escolhida. Agora o driver guarda um fallback e retorna imediatamente o `.cue` quando `preferCue` está ativo para `qpsx`.

O manifesto também contém `ps1_stub_resolver=cue.gba`. A chave é metadata legada: não há um arquivo `cue.gba` no overlay e o código do runtime não referencia essa chave. Ela não é uma dependência de instalação; a seleção efetiva é feita pelo driver e pelo arquivo `.cue` real.

O teste usa uma imagem PS1 homebrew com estes arquivos:

```text
ROMS/PS/compilation.cue
ROMS/PS/compilation.bin
```

O resultado do cartão virtual foi:

```text
RUN qpsx core=qpsx audio=1 frames=180 frameskip=0 rom=/media/mmcblk0/ROMS/PS/compilation.cue
PASS qpsx ret=1 ms=0
```

Isso confirma a seleção correta do arquivo pelo driver e a montagem da ação para o QPSX. Não confirma a execução do binário MIPS no GB300 nem a compatibilidade da BIOS, da imagem ou do jogo específico.

## Verificações executadas

| Verificação | Resultado |
| --- | --- |
| Integridade do ZIP | PASS |
| SHA-256 do firmware com `sha256sum -c` | PASS |
| Sintaxe de todos os JavaScripts | PASS |
| Cabeçalhos OCFU dos 11 cores | PASS |
| Compilação `-Wall -Wextra -Werror` do módulo de controles | PASS |
| GCC static analyzer | PASS |
| AddressSanitizer/UndefinedBehaviorSanitizer | PASS |
| Health-check no cartão virtual | PASS, 8 verificações |
| Frontend-driver core | PASS |
| Frontend-driver frontend | PASS |
| Benchmark SNES | PASS, quatro cenários |
| Seleção de CUE para QPSX | PASS |
| Boot físico, imagem, som, controles e autonomia | PENDENTE |

O firmware entregue tem SHA-256:

```text
904884a8a5ace55645367f0d62145b3403f83041d9f9f96775f592512dddf77a
```

O arquivo ZIP auditado tem SHA-256:

```text
1776bb01a2c2d98b6bb1b27aa075292d44685bf601962a003a10170347036bd8
```

## Diferenças para FrogOS

CajuOS e FrogOS foram comparados no mesmo hardware-alvo e em relação às mesmas convenções observáveis de cartão SD, BIOS, firmware, frontend, dados e cores. O CajuOS mantém identidade, configuração, documentação, tema e diagnósticos próprios.

| Critério | CajuOS v0.3.3-beta | Referência FrogOS/UniFrog |
| --- | --- | --- |
| Objetivo | GB300 e experiência localizada | Base mais conservadora e enxuta |
| Interface | Tema CajuOS, splash e português | Menos personalização no pacote comparado |
| SNES | `snes9x2002` padrão, `snes9x2005` fallback | Core presente, seleção depende do frontend/base |
| PS1 | QPSX com prioridade explícita para CUE | Driver original não tinha essa prioridade no pacote comparado |
| Diagnósticos | Health-check, benchmark e suites de teste | Menos diagnósticos distribuídos |
| Reprodutibilidade | Manifestos e checksum do firmware; source separado | Base pública com Makefile, CI e documentação upstream |
| Risco de release | Maior incerteza por ser beta e hardware não testado | Mais previsível como base conservadora |
| Desempenho | Hipótese favorável em SNES, sem FPS físico | Sem vantagem numérica comprovada |

A conclusão profissional não é que CajuOS seja universalmente melhor ou pior. O FrogOS é a referência conservadora de release; o CajuOS oferece mais personalização e mudanças direcionadas ao GB300, mas ainda exige validação no console.

## Desempenho

Os valores `cpu=918`, `frameskip=1`, `audio=1` e `ge_clock=0` são configurações observáveis no pacote. Eles representam intenção operacional e podem favorecer fluidez em alguns cenários, mas não constituem benchmark. Nenhum resultado desta auditoria deve ser apresentado como FPS medido.

O teste host anterior executou uma ROM GBA real e demos homebrew de SNES, Genesis e PC Engine em emuladores Linux. Essa evidência confirma que as ROMs funcionam no host e que os formatos são válidos; ela não prova que os cores do CajuOS produzirão o mesmo resultado no GB300.

## Instalação e recuperação

O pacote é overlay. Faça imagem integral do cartão original, extraia o conteúdo na raiz de uma cópia, preserve `ROMS/`, saves e BIOS pessoais e use FAT32. Não use Rufus, Etcher ou `dd` para gravar o ZIP. O primeiro teste deve validar apenas boot, menu e controles. Em caso de tela preta antes do menu, restaure a imagem original.

## Riscos residuais

A principal limitação é ausência de teste físico. Também permanecem dependências de hardware e de conteúdo: BIOS PS1 legítima, formato CUE/BIN correto, variante GB300, tela IPS, cartão compatível, áudio e configuração de controles. A reprodução completa exige o pacote de source, patch, toolchain e SDK descritos separadamente; o overlay executável não deve ser confundido com uma distribuição de desenvolvimento completa.

## Referências

[1]: https://github.com/axgdev/UniFrog "UniFrog — repositório upstream"
[2]: https://github.com/axgdev/UniFrog/tree/v0.5.2 "UniFrog v0.5.2"
[3]: https://github.com/nummacway/gb300 "Referência pública do GB300"
[4]: https://github.com/axgdev/UniFrog/issues/7 "Issue upstream sobre desempenho SNES com áudio"
[5]: https://github.com/ArtemioUrbina/240pTestSuite "Homebrew 240p Test Suite usado na validação host"
