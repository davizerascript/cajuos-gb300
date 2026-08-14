# Aviso de beta — CajuOS GB300 v0.3.3

O **CajuOS GB300 v0.3.3-beta** é software experimental. A release passou verificações estruturais, testes em cartão virtual e validações host, mas **não foi inicializada em um GB300 físico pelo mantenedor desta publicação**.

## Riscos

Podem ocorrer falha de boot, tela preta, congelamento, áudio ausente ou distorcido, controles incorretos, incompatibilidade com cartão SD, perda de saves, desempenho abaixo do esperado, consumo elevado e incompatibilidade com alguma revisão de GB300. O risco é maior em cartões sem backup, consoles modificados e imagens PS1 mal formadas.

## Procedimento obrigatório

Faça uma imagem integral do cartão original antes de testar. Use uma cópia, extraia o pacote na raiz e preserve ROMs, saves e BIOS pessoais. Não grave o ZIP inteiro como se fosse uma imagem de disco. Se o console não iniciar, desligue, restaure a imagem original e reporte o comportamento sem publicar arquivos protegidos.

## Escopo

Este pacote é **exclusivo para o DataFrog GB300** e não deve ser usado em outros consoles. A compatibilidade entre variantes GB300 v1/v2, telas IPS, cartões e revisões de bootloader ainda precisa de confirmação física.

## O que a auditoria confirmou

A auditoria confirmou integridade do pacote, checksum de firmware, sintaxe dos scripts, cabeçalhos OCFU, compilação e sanitizers do módulo de controles, health-check virtual, testes do frontend e a prioridade de `.cue` no driver QPSX quando `.cue` e `.bin` coexistem.

Esses resultados **não** confirmam boot físico, FPS, latência, qualidade de áudio, autonomia, temperatura, estabilidade elétrica ou compatibilidade de todas as ROMs no GB300.

## Conteúdo não incluído

O projeto não distribui ROMs comerciais, BIOS proprietárias ou saves pessoais. Use somente conteúdo que você possui ou que tenha autorização para usar, incluindo homebrew e demos com licença compatível.

## Relatos de problemas

Inclua variante do console, revisão de tela, marca/capacidade do cartão, se o cartão original ainda inicia e o sintoma observado. Remova BIOS, ROMs, saves e dados pessoais antes de anexar logs a uma issue pública.
