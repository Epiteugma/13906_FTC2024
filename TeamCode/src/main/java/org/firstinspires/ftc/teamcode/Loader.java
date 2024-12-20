package org.firstinspires.ftc.teamcode;

import android.content.Context;
import android.util.Log;

import org.firstinspires.ftc.ftccommon.external.OnCreate;

public class Loader {
    @OnCreate
    public static void load(Context _) {
        System.loadLibrary("teamcode");
        Log.i("REVVED UP", "LOADED NATIVE MODULE");
    }
}
