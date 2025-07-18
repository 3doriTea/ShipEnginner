#pragma once
#include "Analyzer.h"
#include <map>
#include <string>

class SemanticAnalyzer : public Analyzer<
	SemanticAnalyzer,
	std::pair<Nodes&, Tokens&>,
	ByteCodes,
	SOURCE_POS>
{
private:
	struct FuncData
	{
		FuncData() :
			index{ -1 },
			byteCodes{}
		{}

		int retTypeSize;
		int index;
		ByteCodes byteCodes;
	};

	struct UseMemory
	{
		UseMemory() :
			UseMemory{ -1, 0 }
		{}
		UseMemory(const int _offset, const int _size) :
			offset{ _offset },
			size{ _size }
		{}

		int offset;        // 仕様メモリ位置
		int size;          // 使用メモリサイズ
	};

	struct TypeInfo
	{
		enum Type
		{
			INT,
			BOOL,
		};
	};
public:
	using Analyzer::Analyzer;
	/// <summary>
	/// 解析する
	/// </summary>
	void Analyze() override;

private:
	SOURCE_POS GetSrcPos(const NODE* n);

	/// <summary>
	/// メモリ領域を確保する
	/// </summary>
	/// <param name="name">空間の名前</param>
	/// <param name="size">要求サイズ</param>
	/// <returns>確保できたメモリの番地</returns>
	int NewMemory(const std::string name, int size);

	/// <summary>
	/// 付けた名前からメモリの領域を取得する
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	int GetMemory(const std::string& name);

	void WriteFuncCall(const SOURCE_POS srcPos, ByteCodes& bc, int dest);

	void RegSet(const SOURCE_POS srcPos, int value, ByteCodes& bc, int offset = 0);
	void RegSet(const SOURCE_POS srcPos, const Byte value, ByteCodes& bc, int offset = 0);

	void Read(const NODE* n, const int _depth, int position = 0);
	void ReadFuncDec(const NODE* n, ByteCodes& bc, int position);
	std::string ReadName(const NODE* n);

	std::string ReadFuncName(const NODE* n, ByteCodes& bc);

	/// <summary>
	/// 型を取得 = 型のサイズ を取得
	/// </summary>
	/// <param name="n"></param>
	/// <returns>型の byte サイズ</returns>
	int ReadType(const NODE* n);
	int ReadInteger(const NODE* n);
	void ReadParam(const NODE* n, ByteCodes& bc);
	void ReadProcs(const NODE* n, ByteCodes& bc, int begin);

	void ReadGlobal(const NODE* n, int begin, ByteCodes& bc, int& updateIndex, bool& isFoundUpdate);

	void ReadRet(const NODE* n, ByteCodes& bc);

	void ReadArg(const NODE* n, ByteCodes& bc);

	void ReadNFor(const NODE* n, ByteCodes& bc, int position);

	void ReadNIf(const NODE* n, ByteCodes& bc, int position);

	void ReadExpr(const NODE* n, ByteCodes& bc);

	void ReadAssign(const NODE* n, ByteCodes& bc, const int typeSize, const bool newDec = false);

	void ReadIncrement(const NODE* n, ByteCodes& bc);
	void ReadDecrement(const NODE* n, ByteCodes& bc);

	/// <summary>
	/// 変数の参照し、スタックに追加
	/// </summary>
	/// <param name="n"></param>
	/// <param name="bc"></param>
	void ReadVar(const NODE* n, ByteCodes& bc);

	/// <summary>
	/// 変数を宣言し、メモリ確保する
	/// </summary>
	/// <param name="n"></param>
	/// <param name="bc"></param>
	/// <param name="allowInit">初期化代入可能 true / false</param>
	/// <param name="consecutive ">連続宣言可能か true / false</param>
	void ReadVarDec(const NODE* n, ByteCodes& bc, bool allowInit = false, bool consecutive = false);

	/// <summary>
	/// 関数を参照し、実行するコードを追記
	/// </summary>
	/// <param name="n"></param>
	/// <param name="bc"></param>
	void ReadCallFunc(const NODE* n, ByteCodes& bc);

	/// <summary>
	/// レジスタからメモリに値をセットする
	/// </summary>
	/// <param name="_addr"></param>
	/// <param name="_size"></param>
	/// <param name="bc"></param>
	void MemorySet(const SOURCE_POS srcPos, const int _addr, const int _size, ByteCodes& bc);

	/// <summary>
	/// メモリからレジスタに値をセットする
	/// </summary>
	/// <param name="_addr"></param>
	/// <param name="_size"></param>
	/// <param name="bc"></param>
	void MemoryGet(const SOURCE_POS srcPos, const int _addr, const int _size, ByteCodes& bc);

	/// <summary>
	/// レジスタからスタックに値をプッシュする
	/// </summary>
	/// <param name="_regOffset"></param>
	/// <param name="_size"></param>
	/// <param name="bc"></param>
	void StackPush(const SOURCE_POS srcPos, const int _regOffset, const int _size, ByteCodes& bc);
	/// <summary>
	/// スタックにレジスタから値をポップする
	/// </summary>
	/// <param name="_regOffset"></param>
	/// <param name="_size"></param>
	/// <param name="bc"></param>
	void StackPop(const SOURCE_POS srcPos, const int _regOffset, const int _size, ByteCodes& bc);

	/// <summary>
	/// 基底クラスに渡す用
	/// </summary>
	/// <returns></returns>
	SemanticAnalyzer& Get() override { return *this; }
	/// <summary>
	/// エラー処理
	/// </summary>
	/// <param name="_message">エラーメッセージ</param>
	//void Error(const char* _message) override;

	void Error(const NODE* n, const char* _message);
	/// <summary>
	/// エラー処理
	/// </summary>
	/// <param name="_message">エラーメッセージ</param>
	void Error(const NODE* n, const std::string& _message);


	int maxMemorySize{};
	std::map<std::string, UseMemory> memory{};
	std::map<std::string, FuncData> funcGroup{};
};
