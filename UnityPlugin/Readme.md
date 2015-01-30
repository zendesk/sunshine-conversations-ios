# Using SupportKit with Unity

With SupportKit you can easily add great in-app messaging, documentation and support to your Unity game in less than 10 minutes.

## Step 1: Download SupportKit and Configure the Unity Plugin

You can download SupportKit by cloning our repository on GitHub or grabbing a zip with the latest code.

In it, you will find the following files

**SupportKit.framework** : The core SupportKit SDK
**SupportKit.bundle** : Resources for the SupportKit UI
**UnityPlugin/plugin/** : The Unity plugin code
**UnityPlugin/scripts/** : Required build scripts to plug SupportKit into the Unity iOS player

Note the location to which you have downloaded the SupportKit files. You'll need to enter this *full path* in the file **UnityPlugin/scripts/PostProcessBuildPlayer**. Simply replace the string `FULL_PATH_TO_SUPPORTKIT_GOES_HERE` on line 15 of the file with the path to SupportKit on your machine.

## Step 2: Add SupportKit to your Unity project

Copy the files within **UnityPlugin/plugin/** into **$UNITY_PROJECT_HOME/Assets/Plugins**

Then, copy the contents of **UnityPlugin/scripts/** into **$UNITY_PROJECT_HOME/Assets/Editor**

## Step 3: Initializing SupportKit in your Game

First, ensure that you've signed up for an app token on [https://app.supportkit.io](https://app.supportkit.io). Once you've got the token, you're ready to call the `init()` method to initialize SupportKit.

You can use the following example of a Unity class to see how to structure your calls to SupportKit.

	public class MyGameControl : MonoBehaviour
	{
    	private SupportKit sk;

	    void Start () {
    	    this.sk = new SupportKit();
    	    sk.init("APP_TOKEN_GOES_HERE");
	    }

    	void onGUI () {
        	...
	
    	    // Show SupportKit when your users tap the 'helpButton'
        	if (MenuButton (helpButton))
	        {
    	        sk.show();
        	}
    	}
	}
