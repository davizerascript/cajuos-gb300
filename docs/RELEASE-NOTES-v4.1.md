# CajuOS GB300 4.1

## Resumo

O CajuOS GB300 4.1 mantém as funções de desempenho da versão anterior e atualiza a apresentação do sistema no cartão SD. Os diretórios públicos agora são `Caju OS/` e `Caju OS Data/`, e o firmware distribuído é `Caju OS/firmware/cajuos.bin`.

A alteração foi implementada no firmware MIPS/HCRTOS, no primeiro estágio de boot, no frontend nativo, no host Libretro, no runtime JS2300, nos scripts de diagnóstico, no empacotador e nos testes de distribuição. Não foi feita apenas uma troca cosmética no ZIP.

## Novidades

| Área | Alteração |
| --- | --- |
| Identidade pública | Diretórios visíveis `Caju OS/` e `Caju OS Data/` |
| Firmware | Nome público `cajuos.bin` |
| Boot | Fastboot recompilado para carregar `Caju OS/firmware/cajuos.bin` |
| Runtime | Raízes de firmware, cores, scripts, saves, logs, temas e idiomas atualizadas |
| Frontend | Navegação e mensagens atualizadas para os nomes CajuOS |
| Instalação | Tutorial completo em `docs/INSTALL-CajuOS-GB300.md` |
| Desempenho | Menu pré-jogo e Performance Manager preservados |

## Instalação

Leia [`docs/INSTALL-CajuOS-GB300.md`](INSTALL-CajuOS-GB300.md) antes de instalar. Baixe o arquivo `CajuOS-GB300-v4.1-sdcard.zip` na página de release, verifique o SHA-256, faça backup integral do cartão original e extraia o conteúdo diretamente na raiz de uma cópia do cartão.

A raiz deve conter `Caju OS/`, `Caju OS Data/`, `ROMS/` e `bios/`. Não coloque o conteúdo dentro de uma pasta intermediária e não use Rufus, Etcher ou `dd`, pois o ZIP é um pacote de arquivos e não uma imagem de disco.

## Build e validação

A árvore fonte está em `source/CajuOS-GB300-v4.1`. Os alvos principais são:

```bash
cd source/CajuOS-GB300-v4.1
make doctor
make deps
make quick-check
make check
make sd-zip
```

O script `scripts/build-cajuos-release.sh` copia o estágio interno do build para uma área temporária e renomeia as pastas para os nomes públicos antes de criar o ZIP final. Essa separação evita ambiguidades de shell durante a compilação e garante que o usuário receba somente `Caju OS/` e `Caju OS Data/`.

## Desempenho

O menu pré-jogo oferece `Compatibility`, `Balanced`, `Performance` e `Ultra`, além de CPU, GPU/GE, frameskip, áudio e `Skip duplicate frames`. O perfil `Balanced` é recomendado para o primeiro boot. Os perfis agressivos devem ser avaliados por jogo, especialmente em SNES, GBA, PCE e PS1.

## Limitações

A compilação MIPS, os smoke tests, a auditoria de ZIP e os testes de ROM no host não substituem a validação no GB300 físico. LCD, áudio, controles, clocks, FPS, consumo, compatibilidade de cartão e o boot efetivo precisam ser confirmados com um aparelho real.
