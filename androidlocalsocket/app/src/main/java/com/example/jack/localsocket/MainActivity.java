package com.example.jack.localsocket;

import android.app.Activity;
import android.net.LocalSocket;
import android.net.LocalSocketAddress;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;


public class MainActivity extends Activity {

    private LocalSocket socket;
    private LocalSocket monsock;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

/*        monsock = new LocalSocket();

        try {
            monsock.connect(new LocalSocketAddress("b2apmon"));

            // Send the port's value to create B2AP_Ipc for the port
            ByteBuffer buf = ByteBuffer.allocate(2);
            buf.order(ByteOrder.LITTLE_ENDIAN);
            buf.putShort((short) 10000);
            monsock.getOutputStream().write(buf.array(), 0, 2);

        } catch (IOException e) {
            e.printStackTrace();
            Log.d("ACP", "Error" + e.getMessage().toString());
        }*/


        Button btn = (Button) findViewById(R.id.button);

        btn.setOnClickListener( new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                EditText abtname = (EditText) findViewById(R.id.editText);

                try {
                    socket = new LocalSocket();
                    Log.d("ACP", "Request connet " + abtname.getText().toString());

                    socket.connect(new LocalSocketAddress(abtname.getText().toString()));
                    Toast.makeText(getApplicationContext(), "Connected",Toast.LENGTH_SHORT).show();
                    socket.close();

                } catch (IOException e) {

                    e.printStackTrace();
                }


            }
        });
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
