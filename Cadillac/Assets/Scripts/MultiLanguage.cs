using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class MultiLanguage : MonoBehaviour {
	public enum Language {
		EN,
		CN,
		TW
	};
	
	private static string[] _ColumnFirstLine = new string[] {};
	
	private static List<List<string>> _Cells;
	
	/// <summary>
	/// The Language, default is cn
	/// </summary>
	private static Language _CurrentLanguage = Language.CN;
	private static int _IdxIdLanguage = -1;

	void Awake() {
		MultiLanguage.init();
		MultiLanguage.setupLanguage(_CurrentLanguage);
	}

	void Start () {	
	}
	
	void Update () {	
	}
	
	public static void init() {
		string data = Resources.Load("ref_list").ToString();
		
		string []rows = data.Split('\n');
		
		int rowCount = rows.Length;
		
		if (rowCount > 0) {
			_ColumnFirstLine = rows[0].Split('\t');
		}
		
		_Cells = new List<List<string>>();
		
		int i;
		int j;
		
		for (i = 0; i < _ColumnFirstLine.Length; i++) {
			_ColumnFirstLine[i] = _ColumnFirstLine[i].Trim();
		}
		
		for (i = 0; i < _ColumnFirstLine.Length; i++) {
			_Cells.Add(new List<string>(rowCount));
			for (j = 0; j < rowCount; j++) {
				_Cells[i].Add("");
			}
		}
		
		for (i = 0; i < rowCount; i++) {
			string[] rowDatas = rows[i].Split('\t');
			
			for (j = 0; j < rowDatas.Length; j++) {
				_Cells[j][i] = rowDatas[j];
			}
		}
	}
	
	/// <summary>
	/// Setups the language.
	/// </summary>
	/// <param name="language">Language.</param>
	public static void setupLanguage(Language language) {
		_CurrentLanguage = language;
		_IdxIdLanguage = System.Array.IndexOf(_ColumnFirstLine, language.ToString());
	}
	
	/// <summary>
	/// Get the string text with specified key.
	/// </summary>
	/// <param name="key">Key.</param>
	public static string get(string key) {
		if (_Cells.Count > 0) {
			int index = _Cells[0].IndexOf(key);
			if (index >= 0) {
				return _Cells[_IdxIdLanguage][index];
			}
		}
		Debug.Log("MultiLanguage can't find the key " + key);
		return key;
	}
}
