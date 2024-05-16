void send_coordinates(){
	i=0;
while(1){
	if(lat_int[i]==0)
		break;
	sprintf(str, "%d", lat_int[i]);
	printstring(str);
	i++;
printstring("\n");
}
printstring("latdone\n\n");
i=0;
while(1){
		if(lon_int[i]==0)
		break;
sprintf(str, "%d", lon_int[i]);
	printstring(str);
	i++;
printstring("\n");
}
printstring("logdone\n\n");

sprintf(strs, "%d", distance_sent);
printstring(strs);
printstring("\n");
printstring("done\n\n");
}
//ahmed hany mostafa ahmed 2100741
