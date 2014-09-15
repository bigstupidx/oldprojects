using UnityEngine;
using System.Collections;

public class UIMultiLanguageLabel : MonoBehaviour {

	void Start () {
		GameObject parent = gameObject.transform.parent.gameObject;
		UILabel label = (UILabel)gameObject.GetComponent("UILabel");

		// get the prefix of button
		int spaceIndex = parent.name.IndexOf(" Button");
		string name = parent.name.Substring(0, spaceIndex);
		// Debug.Log ("name = " + name + ", space index = " + spaceIndex.ToString());

		// set the label text
		if (name != null) {
			label.text = MultiLanguage.get(name);
		} else {
			label.text = "Button";
		}
	}
	
	void Update () {
	
	}
}
