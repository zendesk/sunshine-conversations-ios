# Using Smooch with Unity

With Smooch you can easily add great in-app messaging, documentation and support to your Unity game in less than 10 minutes.

## Step 1: Download Smooch and Configure the Unity Plugin

You can download Smooch by cloning our repository on GitHub or grabbing a zip with the latest code.

In it, you will find the following files

**Smooch.framework** : The core Smooch SDK
**Smooch.bundle** : Resources for the Smooch UI
**UnityPlugin/plugin/** : The Unity plugin code
**UnityPlugin/scripts/** : Required build scripts to plug Smooch into the Unity iOS player

Note the location to which you have downloaded the Smooch files. You'll need to enter this *full path* in the file **UnityPlugin/scripts/PostProcessBuildPlayer**. Simply replace the string `FULL_PATH_TO_SMOOCH_GOES_HERE` on line 15 of the file with the path to Smooch on your machine.

## Step 2: Add Smooch to your Unity project

Copy the files within **UnityPlugin/plugin/** into **$UNITY_PROJECT_HOME/Assets/Plugins**

Then, copy the contents of **UnityPlugin/scripts/** into **$UNITY_PROJECT_HOME/Assets/Editor**

## Step 3: Initializing Smooch in your Game

First, ensure that you've signed up for an app token on [https://app.smooch.io](https://app.smooch.io). Once you've got the token, you're ready to call the `init()` method to initialize Smooch.

You can use the following example of a Unity class to see how to structure your calls to Smooch.

	public class MyGameControl : MonoBehaviour
	{
    	private Smooch sk;

	    void Start () {
    	    this.sk = new Smooch();
    	    sk.init("APP_TOKEN_GOES_HERE");
	    }

    	void onGUI () {
        	...
	
    	    // Show Smooch when your users tap the 'helpButton'
        	if (MenuButton (helpButton))
	        {
    	        sk.show();
        	}
    	}
	}
