# CajuOS GB300

**CajuOS GB300 4.1** é um projeto independente de firmware, frontend nativo, cores Libretro e ferramentas de desempenho para o console portátil GB300. O sistema foi desenvolvido para o hardware HCRTOS/MIPS do aparelho e inclui um menu pré-jogo com perfis de desempenho.

**Autor e mantenedor:** [@melo._.071 no Instagram](https://www.instagram.com/melo._.071/) e [`davizerascript` no GitHub](https://github.com/davizerascript).

> **Estado do projeto:** experimental. A build, o empacotamento e os testes host foram validados, mas boot, LCD, áudio, controles, clocks reais, FPS e autonomia ainda precisam ser confirmados em um GB300 físico. Faça sempre um backup integral do cartão original.

## Download e instalação

O arquivo correto para uma instalação normal é o pacote `CajuOS-GB300-v4.1-sdcard.zip`, disponível na página de [releases do GitHub](https://github.com/davizerascript/cajuos-gb300/releases). O pacote fonte é destinado a desenvolvedores e não deve ser instalado no cartão.

Leia o [tutorial completo de instalação](docs/INSTALL-CajuOS-GB300.md) antes de modificar o cartão. O ZIP é um pacote de arquivos, não uma imagem de disco: não use Rufus, Etcher ou `dd` para gravá-lo. Extraia o conteúdo diretamente na raiz de uma cópia do cartão que já inicia no GB300.

Depois da extração, a estrutura pública deve ser:

```text
Cartão SD/
├── Caju OS/
│   ├── cores/
│   ├── firmware/cajuos.bin
│   └── manifest.ini
├── Caju OS Data/
│   ├── languages/
│   ├── scripts/
│   └── settings.ini
├── ROMS/
├── bios/
├── README-CAJUOS.txt
└── REPRODUCE-CAJUOS.txt
```

Não deixe o conteúdo dentro de uma pasta intermediária com o nome do ZIP. O CajuOS não distribui ROMs comerciais, BIOS proprietárias ou saves pessoais.

## Menu de desempenho

Após a seleção de uma ROM e do core, o frontend abre o menu pré-jogo. A pessoa pode iniciar o jogo ou escolher um perfil de desempenho antes do lançamento.

| Opção | Função |
| --- | --- |
| `Start game` | Inicia a ROM com as escolhas atuais. |
| `Compatibility` | Perfil conservador para compatibilidade e estabilidade. |
| `Balanced` | Perfil recomendado para o primeiro teste. |
| `Performance` | Reduz filtros e custos de apresentação quando possível. |
| `Ultra` | Perfil agressivo para jogos que precisam de mais margem de desempenho. |
| `CPU` | Ajusta o perfil de CPU suportado pelo firmware. |
| `GPU/GE` | Ajusta o perfil do acelerador gráfico. |
| `Frameskip` | Controla o descarte de frames para aliviar a carga. |
| `Audio` | Ajusta a política de áudio do core e do host. |
| `Skip duplicate frames` | Evita reapresentar imagens idênticas em cenas estáticas. |

O Performance Manager aplica automaticamente as opções que cada core expõe. O descarte de frames repetidos usa uma assinatura amostrada do framebuffer; ele reduz trabalho de apresentação em cenas apropriadas, mas não é apresentado como aumento mágico da potência da CPU emulada.

## ROMs e organização

Copie somente conteúdos que você possui legalmente para `ROMS/`. A organização recomendada é:

| Sistema | Pasta | Extensões |
| --- | --- | --- |
| Game Boy Advance | `ROMS/GBA/` | `.gba` |
| SNES | `ROMS/SFC/` | `.sfc`, `.smc` |
| Mega Drive | `ROMS/MD/` | `.md`, `.gen`, `.smd`, `.bin` |
| PC Engine | `ROMS/PCE/` | `.pce`, `.sgx` |
| PlayStation | `ROMS/PS/` | `.cue` com os `.bin` correspondentes |
| NES | `ROMS/NES/` | `.nes` |
| Game Boy | `ROMS/GB/` | `.gb`, `.gbc` |

Para PlayStation, mantenha o `.cue` e todos os arquivos `.bin` referenciados por ele na mesma pasta. O CajuOS prioriza o `.cue` para o core QPSX quando os arquivos coexistem.

## Código-fonte e reprodução

A árvore fonte está em [`source/CajuOS-GB300-v4.1`](source/CajuOS-GB300-v4.1). Para compilar e validar:

```bash
cd source/CajuOS-GB300-v4.1
make doctor
make deps
make quick-check
make check
make sd-zip
```

O script [`scripts/build-cajuos-release.sh`](scripts/build-cajuos-release.sh) monta o pacote final, acrescenta o overlay do CajuOS e atualiza o checksum do firmware. A documentação técnica está em [`docs/CAJUOS-4.0-TEST-REPORT.md`](docs/CAJUOS-4.0-TEST-REPORT.md), enquanto o procedimento para usuários está em [`docs/INSTALL-CajuOS-GB300.md`](docs/INSTALL-CajuOS-GB300.md).

## Segurança e recuperação

Se ocorrer tela preta antes do menu, reinício contínuo, travamento no logo, ausência de controles ou falha de áudio, desligue o console e restaure o backup original. Não tente resolver uma falha de boot alterando frameskip, clock, BIOS ou parâmetros do cartão.

Durante uma atualização, preserve as ROMs, saves e BIOS pessoais. O primeiro boot deve ser feito com o perfil `Balanced`; depois, teste `Compatibility`, `Performance` e `Ultra` individualmente conforme a necessidade de cada jogo.

## Licenças

Consulte [`LICENSE`](LICENSE), [`THIRD_PARTY.md`](THIRD_PARTY.md) e os avisos distribuídos nas pastas de componentes. Cada core possui seus próprios termos de redistribuição.

## Referências técnicas

O estudo de compatibilidade do GB300 e os testes de host são mantidos no repositório para facilitar auditoria e reprodução. Referências externas são usadas como documentação técnica, não como definição da identidade do CajuOS.
