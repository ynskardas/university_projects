import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.RandomAccessFile;
import java.util.*;
import java.io.FileWriter;

public class SystemCatalogue {

    public SystemCatalogue(String INPUT_FILE, String OUTPUT_FILE) throws IOException{
        File sysCat = new File("SysCat.txt");
        RandomAccessFile output =new RandomAccessFile (sysCat, "rw");
        output.seek(0);
        boolean dataf = (new File("DataFiles")).mkdir();

        output.writeInt(0);
        int num = 0;
        File myObj = new File(INPUT_FILE);
        Scanner myReader = new Scanner(myObj);
        String writeFile = "";
        while (myReader.hasNextLine()) {
            String data = "";

            String line = myReader.nextLine();
            if (line.contains("create")){
                if (line.contains("type")){
                    num = 1;
                }
                else{
                    num = 4;
                }
            }
            else if (line.contains("delete")){
                if (line.contains("type")){
                    num = 2;
                }
                else {
                    num = 5;
                }
            }
            else if (line.contains("list")){
                if (line.contains("type")){
                    num = 3;
                }
                else {
                    num = 8;
                }
            }
            else if (line.contains("search")){
                num = 6;
            }
            else if (line.contains("update")){
                num = 7;
            }

            if(num==1){
                CreateType(line);
            }
            else if(num==2){
                DeleteType(line);
            }
            else if(num==3){
                data = ListAllTypes(line);
            }
            else if(num==4){
                CreateRecord(line);
            }
            else if(num==5){
                DeleteRecord(line);
            }
            else if(num==6){
                data = SearchRecord(line);
            }
            else if(num==7){
                UpdateRecord(line);
            }
            else if(num==8){
                data = ListAllRecords(line);
            }

            writeFile = writeFile + data;

/*
            System.out.println("-----------------------------");
            System.out.println(line);
            System.out.println(data);

*/

        }

        //    System.out.println(writeFile);

        try {
            FileWriter myWriter = new FileWriter(OUTPUT_FILE);
            myWriter.write(writeFile);
            myWriter.close();
            //        System.out.println("Successfully wrote to the file.");
        } catch (IOException e) {
            //        System.out.println("An error occurred.");
            e.printStackTrace();
        }


    }
    private String ListAllRecords(String line) throws IOException {
        String data = "";
        String[] arr = line.split(" ", 3);

        String typeName = arr[2];
        File f=new File("DataFiles/"+typeName+".txt");
        RandomAccessFile output=new RandomAccessFile(f,"rw");
        output.seek(0);
        int numOfRecords=output.readInt();
        output.seek(4);
        int numOfFields=output.readInt();
        String[] fieldNames=new String[numOfFields];
        for(int i=0;i<numOfFields;i++){
            output.seek(8+10*i);
            String fieldName=output.readUTF();
            fieldNames[i]=fieldName;
        }
        int pcounter=1;
        for(int i=0;i<numOfRecords;i++){
            if(i%32==0&&i!=0){
            }
            output.seek(8+10*numOfFields+(4*numOfFields+1)*i);
            boolean isDeleted=output.readBoolean();
            output.seek(8+10*numOfFields+(4*numOfFields+1)*i+1);
            String fakeData = "";
            for(int j=0;j<numOfFields;j++){
                output.seek(8+10*numOfFields+(4*numOfFields+1)*i+1+j*4);
                int fieldVal=output.readInt();
                fakeData = fakeData + fieldVal + " ";
            }

            if(!isDeleted)
                data = data + fakeData + "\n";

        }
        return data;

    }

    private void UpdateRecord(String line) throws IOException {
        String data = "";
        String[] arr = line.split(" ", 4);

        String typeName = arr[2];
        File f=new File("DataFiles/"+typeName+".txt");
        RandomAccessFile output=new RandomAccessFile(f,"rw");
        output.seek(0);
        int numOfRecords=output.readInt();
        output.seek(4);
        int numOfFields=output.readInt();
        String[] arr2 = arr[3].split(" ", numOfFields);

        int primaryKey=Integer.parseInt(arr2[0]);

        String[] fieldNames=new String[numOfFields];
        boolean canFind=false;
        for(int i=0;i<numOfFields;i++){
            output.seek(8+10*i);
            String fieldName=output.readUTF();
            fieldNames[i]=fieldName;
        }
        int pcounter=1;
        output.seek(8+10*numOfFields);
        for(int i=0;i<numOfRecords;i++){
            if(i%32==0&&i!=0){
                pcounter++;
            }
            output.seek(8+10*numOfFields+(4*numOfFields+1)*i+1);
            if(output.readInt()==primaryKey){
                canFind=true;
                for(int j=0;j<numOfFields;j++){
                    output.seek(8+10*numOfFields+(4*numOfFields+1)*i+1+j*4);
                    output.writeInt(Integer.parseInt(arr2[j]));

                }
                output.seek(8+10*numOfFields+(4*numOfFields+1)*i);
                if(output.readBoolean()){
                    //System.out.println("This record has been deleted");
                }
                canFind=true;
            }

        }

        if(!canFind){
            return;
        }
        return;

    }

    private String SearchRecord(String line) throws IOException {
        String data = "";
        String[] arr = line.split(" ", 4);

        String typeName = arr[2];

        if(!alreadyExists(typeName)){
            return data;
        }

        File f=new File("DataFiles/"+typeName+".txt");
        RandomAccessFile output=new RandomAccessFile(f,"rw");
        output.seek(0);
        int numOfRecords=output.readInt();
        output.seek(4);
        int numOfFields=output.readInt();

        int primaryKey=Integer.parseInt(arr[3]);

        String[] fieldNames=new String[numOfFields];
        boolean canFind=false;
        for(int i=0;i<numOfFields;i++){
            output.seek(8+10*i);
            String fieldName=output.readUTF();
            fieldNames[i]=fieldName;
        }
        int pcounter=1;
        output.seek(8+10*numOfFields);
        for(int i=0;i<numOfRecords;i++){
            if(i%32==0&&i!=0){
                pcounter++;
            }
            output.seek(8+10*numOfFields+(4*numOfFields+1)*i+1);
            if(output.readInt()==primaryKey){
                canFind=true;
                for(int j=0;j<numOfFields;j++){
                    output.seek(8+10*numOfFields+(4*numOfFields+1)*i+1+j*4);
                    int s=output.readInt();
                    data = data + s + " ";

                }
                data = data + "\n";
                output.seek(8+10*numOfFields+(4*numOfFields+1)*i);
                if(output.readBoolean()){
                }
                canFind=true;
            }

        }
        if(!canFind){
            return "";
        }
        return data;
    }

    private void DeleteRecord(String line) throws IOException {
        String[] arr = line.split(" ", 4);

        String typeName = arr[2];
        File f=new File("DataFiles/"+typeName+".txt");
        RandomAccessFile output =new RandomAccessFile (f, "rw");
        output.seek(0);
        int numOfRecords=output.readInt();
        output.seek(4);
        int numOfFields=output.readInt();
        int primaryKey=Integer.parseInt(arr[3]);
        output.seek(8+10*numOfFields);
        boolean canDelete=false;
        int pcounter=1;
        for(int i=0;i<numOfRecords;i++){
            if(i%32==0&&i!=0){
                pcounter++;
            }
            output.seek(8+10*numOfFields+(4*numOfFields+1)*i);
            if(!output.readBoolean()){
                output.seek(8+10*numOfFields+(4*numOfFields+1)*i+1);
                int fieldVal=output.readInt();
                if(fieldVal==primaryKey){
                    output.seek(8+10*numOfFields+(4*numOfFields+1)*i);
                    output.writeBoolean(true);
                    canDelete=true;
                    break;
                }
            }
        }
        if(!canDelete) {
            //System.out.println("There's no record with the given primary key.");
        }
    }
    private void CreateRecord(String line) throws IOException {
        String[] arr = line.split(" ", 4);


        String typeName = arr[2];
        File f=new File("DataFiles/"+typeName+".txt");
        RandomAccessFile output =new RandomAccessFile (f, "rw");
        output.seek(0);
        int numOfRecords=output.readInt();
        numOfRecords++;
        output.seek(0);
        output.writeInt(numOfRecords);
        output.seek(4);
        int numOfFields = output.readInt();
        int []fieldValues=new int[numOfFields];
        String[] arr2 = arr[3].split(" ", numOfFields);
        for(int i=0;i<numOfFields;i++){
            output.seek(8+10*i);
            String fieldName=output.readUTF();
            fieldValues[i]=Integer.parseInt(arr2[i]);
        }

        output.seek(8+10*numOfFields+((4*numOfFields+1)*(numOfRecords-1)));
        output.writeBoolean(false);
        output.seek(8+10*numOfFields+((4*numOfFields+1)*(numOfRecords-1))+1);
        int pcounter=1;
        for(int i=0;i<numOfRecords;i++){
            if(i%32==0&&i!=0){
                pcounter++;
            }
        }
        for(int i=0;i<numOfFields;i++){
            output.seek(8+10*numOfFields+((4*numOfFields+1)*(numOfRecords-1))+1+4*i);
            output.writeInt(fieldValues[i]);
        }


    }
    private String ListAllTypes(String line) throws IOException {
        String data = "";
        File sysCat = new File("SysCat.txt");
        RandomAccessFile output =new RandomAccessFile (sysCat, "rw");
        output.seek(0);
        int numOfTypes=output.readInt();
        output.seek(4);
        for(int i=0;i<numOfTypes;i++){
            output.seek(4+115*i);
            String typeName=output.readUTF();
            output.seek(1+115*i+14);
            boolean isDeleted=output.readBoolean();
            if(!isDeleted)
                data = data + typeName + "\n";
        }
        return data;
    }
    private void DeleteType(String line) throws IOException {
        String[] arr = line.split(" ", 3);

        String typeName = arr[2];

        File f=new File("DataFiles/"+typeName+".txt");
        f.delete();
        File sysCat = new File("SysCat.txt");
        RandomAccessFile output =new RandomAccessFile (sysCat, "rw");
        output.seek(0);
        int numOfTypes=output.readInt();
        output.seek(4);
        for(int i=0;i<numOfTypes;i++){
            output.seek(4+115*i);
            String type=output.readUTF();
            if(type.equals(typeName)){
                output.seek(1+115*i+14);
                output.writeBoolean(true);
            }

        }

    }
    private void CreateType(String line) throws IOException {

        String[] arr = line.split(" ", 5);

        String typeName = arr[2];
        if(alreadyExists(typeName)|typeName.length()>10|typeName.length()==0){
            return;
        }
        File record=new File("DataFiles/"+typeName+".txt");

        int numOfFields=Integer.parseInt(arr[3]);
        String[] fieldNames=new String[numOfFields];

        String[] arr2 = arr[4].split(" ", numOfFields);

        for(int i = 0; i < numOfFields; i++){

            fieldNames[i]=arr2[i];
        }
        RandomAccessFile out = new RandomAccessFile(record , "rw");
        out.seek(0);
        out.writeInt(0);
        out.seek(4);
        out.writeInt(numOfFields);
        out.seek(8);
        for(int i=0;i<numOfFields;i++){
            out.seek(8+10*i);
            out.writeUTF(fieldNames[i]);
        }

        File sysCat = new File("SysCat.txt");
        RandomAccessFile output =new RandomAccessFile (sysCat, "rw");
        output.seek(0);
        int numOfTypes=output.readInt();
        numOfTypes++;
        output.seek(0);
        output.writeInt(numOfTypes);
        output.seek((numOfTypes - 1) * 115 + 4);
        output.writeUTF(typeName);
        output.seek((numOfTypes - 1) * 115 + 14);
        output.writeInt(numOfFields);
        output.seek((numOfTypes - 1) * 115 + 18);
        output.writeBoolean(false);
        output.seek((numOfTypes - 1) * 115 + 19);
        for(int i=0;i<fieldNames.length;i++){
            output.seek((numOfTypes - 1) * 115 + 19+i*10);
            output.writeUTF(fieldNames[i]);
        }
    }


    public boolean alreadyExists(String inp){
        File types=new File("DataFiles");
        String[] f=types.list();
        for(int i=0;i<f.length;i++){
            if(f[i].equals(inp+".txt"))
                return true;
        }
        return false;

    }



}