package com.kivvi.ripples.config.parser;

import java.util.ArrayList;
import java.util.HashMap;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

public class xmlParser extends DefaultHandler {
	public configInfo config;

	String nameAttri;
	String localName;
	String targetName;

	public xmlParser(){
	}
	
	public configInfo getConfig(){
		return config;
	}
	
	@Override
	public void startDocument() throws SAXException {
		// TODO Auto-generated method stub
		config = new configInfo();
	}
	
	@Override
	public void startElement(String uri, String localName, String qName,
			Attributes attributes) throws SAXException {
		// TODO Auto-generated method stub
		this.localName = localName;
	}
	
	@Override
	public void characters(char[] ch, int start, int length)
			throws SAXException {
		// TODO Auto-generated method stub
		String str = new String(ch, start, length);
		if(this.localName.equals("frequencyswitch")){
			config.setFrequencyswitch(str);
		}
		
		if(this.localName.equals("rangeswitch")){
			config.setRangeswitch(str);
		}
		
		if(this.localName.equals("scrollbackgroundswitch")){
			config.setScrollbackgroundswitch(Boolean.parseBoolean(str));
		}
		
		if(this.localName.equals("backgroundoption")){
			config.setBackgroundoption(Integer.parseInt(str));
		}
		
		if(this.localName.equals("custombackgroundpath")){
			config.setCustombackgroundpath(str);
		}
		
		if(this.localName.equals("reflectlight")){
			config.setReflectlight(Boolean.parseBoolean(str));
		}
		
	}

	@Override
	public void endElement(String uri, String localName, String qName)
			throws SAXException {
		// TODO Auto-generated method stub
		this.localName = "";
	}

	@Override
	public void endDocument() throws SAXException {
		// TODO Auto-generated method stub
	}
}
