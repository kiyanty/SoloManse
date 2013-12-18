/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.solo.manse;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

public class SoloManse extends Cocos2dxActivity
{
	static AlertDialog alert;
    private static BackKeyHandler backKeyHandler;	
	public static SoloManse soloManse;
	
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		soloManse = this;
		
		alert = new AlertDialog.Builder(this)
		.setIcon(R.drawable.icon)
		.setTitle("솔로는 외롭지 않아")
		.setMessage("커플을 이대로 방치하고 게임을 종료할까요?")
		.setPositiveButton("예", new DialogInterface.OnClickListener()
		{
			@Override
			public void onClick(DialogInterface dialog, int which)
 			{
 				System.exit(0);
 			}
 		})
 		.setNegativeButton("아니요", null).create();
		
		backKeyHandler = new BackKeyHandler();
	}
	
    static
    {
         System.loadLibrary("game");
    }
    
    public static void goHomepage(int guestId, int score)
    {
		Intent i = new Intent(Intent.ACTION_VIEW);
		Uri u = Uri.parse("http://chilx2.cafe24.com/apps/server/solo/save_Rank.php?id=" + guestId + "&score=" + score);
		i.setData(u);
		soloManse.startActivity(i);
		soloManse.overridePendingTransition(R.anim.fade, 0);    	
    }
    
    public static void backButton()
    {
        backKeyHandler.sendEmptyMessage(0);
    }
    
    private class BackKeyHandler extends Handler
    {
        public void handleMessage(Message msg)
        {
        	if(alert.isShowing())
        	{
    			alert.cancel();    		
        	}
        	else
        	{
        		alert.show();
        	}
        }
    }
    
}
