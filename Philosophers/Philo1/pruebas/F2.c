# include  <pthread.h>
 # include  <stdio.h>
 # include  <unistd.h>  // para dormir

 // Esta función será ejecutada por el hilo separado 
void * print_in_background ( void * arg)
 { 
    printf ( "Esto se imprime desde el hilo.\n" ); 
    sleep ( 5 ); 
    return  NULL ; 
} 

int  main ()  { 
    pthread_t thread_id; 

    // Crear un nuevo hilo 
    if ( pthread_create (&thread_id, NULL , print_in_background, NULL ) != 0 ) 
    { 
        perror ( "Error al crear el hilo" ); 
        return  1 ; 
    } 

    // 🚨 alternar estos 2 🚨 
    //pthread_detach (thread_id); 
    pthread_join(thread_id, NULL); 

    // Continuar con el trabajo del hilo principal 
    printf ( "Esto se imprime desde el hilo principal.\n" ); 
    sleep ( 6 ); 

    return  0 ; 
}