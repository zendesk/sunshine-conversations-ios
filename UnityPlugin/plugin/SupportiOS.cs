/*
 * Copyright 2015, Radialpoint Safecare Inc.
 * All rights reserved
 */

#if UNITY_IPHONE
using UnityEngine;
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using SKMiniJSON;

namespace SupportKitiOS
{
	public class SupportKit
	{

		[DllImport ("__Internal")]
		private static extern void sktInit(string appToken, string settingsDictionaryString);
		[DllImport ("__Internal")]
		private static extern void sktShowConversation ();
		[DllImport ("__Internal")]
		private static extern void sktTrack(string eventName);
		[DllImport ("__Internal")]
		private static extern void sktShow();
		[DllImport ("__Internal")]
		private static extern void sktSetEmail(string email);
		[DllImport ("__Internal")]
		private static extern void sktSetName(string firstName, string lastName);
		[DllImport ("__Internal")]
		private static extern void sktAddProperties(string propertyDictionaryString);

		public SupportKit () {
		}

		public void init (string appToken, Dictionary<string, object> settings) {
			if(settings == null) {
				sktInit (appToken, "");
			} else {
				sktInit (appToken, Json.Serialize(settings));
			}
		}

		public void showConversation() {
			sktShowConversation();
		}

		public void track (string eventName) {
			sktTrack(eventName);
		}

		public void show () {
			sktShow();
		}

		public void setEmail(string email) {
			sktSetEmail(email);
		}

		public void setName(string firstName, string lastName) {
			sktSetName(firstName, lastName);
		}

		public void addProperties(Dictionary <string, object> properties) {
			if(properties != null) {
				sktAddProperties(Json.Serialize(properties));
			}
		}
	}
}
#endif
