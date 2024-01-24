# プロジェクトタイトル

42_minishell

## 概要

![M1n01さん](https://github.com/M1n01)とのチーム制作物です。
shellをC言語で再実装しています。

## プロジェクトの目的

42Tokyoのチーム課題であり、また、  
shellの内部での動きについて学び
正常ケース、エラーケースの把握とともにそれに伴うエラーハンドリング。<br>
適切なfdのopen、close処理、
複雑な再起処理などを、実装できるようなること。

## チャレンジした点

自分はビルトインとパイプ、環境変数担当でしたが、様々なエラーケースに対応するのに苦労しました。  
特にcdのファイルかディレクトリによって変わるエラー表示、　<br>
exportのすでにある値の書き換えの際のリーク漏れのチェックなどが大変でした。　

## 学んだこと、チームワークの重要性

このチーム課題をやるまで、M1n01さんとは話したこともなかったですが、  
役割を決め、issueをたてながら進め、試行錯誤をしました。  
何をどこまで本家に寄せるか、関数や変数名の一貫性を保たせるための話し合いなど  
密なコミュニケーションと自分の意思を伝えることと、相手の意見を聞くことの大切さを学びました。  

また、基本的なshellの実装を学ぶことにより、実際に自分がコマンドを実行する時に  
豊かなバリエーションを持って挑めるようになりました。

## 使用方法

> - **normal**
> ```bash php
> #!/bin/bash
> cd 42_minishell
> make
> ./minishell
> minishell$ ls (お好きなコマンドを試してみてください！)
> ```

minishellから抜けたい時はexitコマンドかコントロールCを押すと抜けられます。

## 技術スタック

C言語
