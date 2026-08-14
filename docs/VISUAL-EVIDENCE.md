# Evidência visual da release beta

As imagens anexadas à release são evidências auxiliares, não uma confirmação de boot no GB300 físico.

| Arquivo | Origem | O que demonstra | O que não demonstra |
| --- | --- | --- | --- |
| `cajuos-menu-preview-contact-sheet.png` | Simulação local 320×240 usando assets e paleta do CajuOS | Organização visual do menu, splash e telas esperadas | LCD real, sincronismo, tearing, áudio ou controles físicos |
| `03-main-menu-simulated.png` | Simulação local do menu principal | Layout de sistemas e textos do tema | Boot real ou desempenho |
| `boot-splash-320x240.png` | Asset do pacote CajuOS | Splash distribuído no overlay | Funcionamento do LCD em hardware |
| `welcome-splash-320x240.png` | Asset do pacote CajuOS | Tela de boas-vindas distribuída | Compatibilidade de cada revisão GB300 |
| `mednafen-snes-screen.png` | Teste host com homebrew 240p Test Suite | Que o conteúdo homebrew foi executado no host | Que o core OCFU executará igual no GB300 |

As duas primeiras imagens são renderizações de simulação. As imagens host foram produzidas em Linux com Mednafen e servem apenas como evidência de conteúdo/formato. A validação física de boot, vídeo, áudio, controles, autonomia e desempenho continua pendente.
