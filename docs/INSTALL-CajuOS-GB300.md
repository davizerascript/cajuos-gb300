# Tutorial de instalação — CajuOS GB300 4.1

## Visão geral

O CajuOS GB300 é distribuído como um **pacote de arquivos para cartão SD**, não como uma imagem de disco. O arquivo correto para instalar é `CajuOS-GB300-v4.1-sdcard.zip`, disponível na página de [releases do repositório](https://github.com/davizerascript/cajuos-gb300/releases).

> **Não grave o ZIP com Rufus, Etcher ou `dd`.** O procedimento correto é extrair o conteúdo do ZIP diretamente na raiz do cartão SD.

O pacote não inclui ROMs comerciais, BIOS proprietárias ou saves pessoais. Esses arquivos continuam sendo responsabilidade do proprietário do console e devem ser copiados somente de fontes legítimas.

## Arquivos disponíveis na release

| Arquivo | Finalidade |
| --- | --- |
| `CajuOS-GB300-v4.1-sdcard.zip` | Pacote pronto para instalar no cartão SD |
| `CajuOS-GB300-source-v4.1.zip` | Código-fonte para desenvolvedores e recompilação |
| `CAJUOS-SDCARD-SHA256SUMS.txt` | Hash do pacote instalável |
| `CAJUOS-SOURCE-SHA256SUMS.txt` | Hash do pacote fonte |

Para uma instalação normal, baixe somente o pacote `sdcard.zip`. O pacote fonte não deve ser extraído no cartão para instalar o sistema.

## Antes de começar

Use um computador com leitor de cartão SD e faça uma cópia integral do cartão original que já inicia no GB300. Essa cópia é a forma mais segura de recuperar o console caso a variante do aparelho ou do cartão não seja compatível.

O console deve estar **desligado** durante a remoção e a inserção do cartão. O cartão deve manter o formato usado pela sua revisão do GB300, normalmente FAT32. Não reformate o cartão se você não tiver uma imagem ou um backup completo que permita restaurá-lo.

## Verificar o download

A release fornece o arquivo `CAJUOS-SDCARD-SHA256SUMS.txt`. No Linux ou macOS, coloque o arquivo de checksum na mesma pasta do ZIP e execute:

```bash
sha256sum -c CAJUOS-SDCARD-SHA256SUMS.txt
```

No Windows PowerShell, execute:

```powershell
Get-FileHash .\CajuOS-GB300-v4.1-sdcard.zip -Algorithm SHA256
```

O valor calculado deve ser igual ao hash publicado na release. Se o hash for diferente, descarte o arquivo e faça o download novamente.

## Instalação em uma cópia do cartão

Com o cartão desmontado e conectado ao computador, abra `CajuOS-GB300-v4.1-sdcard.zip` e extraia **os itens que estão dentro do ZIP**, não uma pasta intermediária. A raiz do cartão deve ficar semelhante a esta:

```text
Cartão SD/
├── Caju OS/
│   ├── cores/
│   ├── firmware/
│   │   └── cajuos.bin
│   ├── manifest.ini
│   └── LICENSE.txt
├── Caju OS Data/
│   ├── cajuos-manifest.ini
│   ├── languages/
│   ├── scripts/
│   └── settings.ini
├── ROMS/
├── bios/
├── README-CAJUOS.txt
└── REPRODUCE-CAJUOS.txt
```

O resultado incorreto é deixar todo o conteúdo dentro de uma pasta com o nome do ZIP:

```text
Cartão SD/
└── CajuOS-GB300-v4.1-sdcard/
    ├── Caju OS/
    ├── Caju OS Data/
    └── ROMS/
```

Se o programa de extração criar essa pasta intermediária, abra-a e copie `Caju OS`, `Caju OS Data`, `ROMS`, `bios` e os arquivos de texto para a raiz do cartão.

Durante uma atualização, faça primeiro o backup dos diretórios de sistema existentes. Depois, substitua os diretórios de runtime pela versão nova. Não apague `ROMS`, saves ou BIOS pessoais sem ter uma cópia fora do cartão.

## Copiar ROMs

O CajuOS não distribui jogos. Copie somente ROMs e imagens que você possui legalmente para `ROMS/`. A organização recomendada é:

| Sistema | Pasta | Extensões comuns |
| --- | --- | --- |
| Game Boy Advance | `ROMS/GBA/` | `.gba` |
| SNES | `ROMS/SFC/` | `.sfc`, `.smc` |
| Mega Drive | `ROMS/MD/` | `.md`, `.gen`, `.smd`, `.bin` |
| PC Engine | `ROMS/PCE/` | `.pce`, `.sgx` |
| PlayStation | `ROMS/PS/` | `.cue` com os `.bin` correspondentes |
| NES | `ROMS/NES/` | `.nes` |
| Game Boy | `ROMS/GB/` | `.gb`, `.gbc` |

Para PlayStation, mantenha o arquivo `.cue` e todos os arquivos `.bin` referenciados por ele na mesma pasta. Para Mega Drive, deixe os arquivos `.bin` dentro de `ROMS/MD/`, pois essa extensão também pode ser usada por imagens de outros sistemas.

## Primeiro boot

Ejete o cartão SD pelo sistema operacional, insira-o no GB300 desligado e ligue o console. O primeiro teste deve ser conservador: confirme o boot, a imagem, os botões e a abertura da biblioteca de ROMs antes de testar jogos exigentes.

Ao escolher uma ROM, o CajuOS abre o menu pré-jogo. Para o primeiro teste, selecione o perfil **Balanced** e pressione **Start game**. Depois que a execução básica estiver confirmada, teste os perfis `Compatibility`, `Performance` e `Ultra` conforme a capacidade do jogo.

O menu também permite ajustar CPU, GPU/GE, frameskip, áudio e `Skip duplicate frames`. Se um jogo apresentar falhas gráficas ou incompatibilidade, volte para `Compatibility`. Se houver lentidão, teste `Performance` antes de usar `Ultra`.

## Se o console não iniciar

Se ocorrer tela preta antes do menu, reinício contínuo, travamento no logo, ausência de controles ou falta de áudio, desligue o GB300 e restaure a cópia original do cartão. Não tente resolver uma falha de boot alterando frameskip, clock, BIOS ou parâmetros de SD.

Confirme também se `Caju OS/` e `Caju OS Data/` estão diretamente na raiz do cartão e se o arquivo `Caju OS/firmware/cajuos.bin` existe. Um ZIP dentro de outra pasta ou um firmware copiado para um caminho diferente não será encontrado pelo bootloader recompilado do CajuOS.

## Limitações conhecidas

A validação estrutural, a compilação MIPS, a auditoria do ZIP e os testes host não substituem um teste em um GB300 físico. A primeira instalação deve ser feita com backup integral do cartão original e, idealmente, em uma unidade cuja revisão de hardware já tenha sido confirmada.

Para consultar a implementação e reproduzir a compilação, use o [pacote fonte](https://github.com/davizerascript/cajuos-gb300/releases) e o documento [`REPRODUCE-CAJUOS.txt`](../overlay/REPRODUCE-CAJUOS.txt).
