#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct video {
  char *title;
  char *url;
};

struct video *videos;
int num_videos = 0;

void add_video(char *title, char *url) {
  struct video *new_video = malloc(sizeof(struct video));
  new_video->title = strdup(title);
  new_video->url = strdup(url);

  videos = realloc(videos, (num_videos + 1) * sizeof(struct video));
  videos[num_videos++] = *new_video;
}

void save_videos_to_csv(char *filename) {
  FILE *fp = fopen(filename, "w");
  if (fp == NULL) {
    printf("Error opening file %s\n", filename);
    return;
  }

  for (int i = 0; i < num_videos; i++) {
    fprintf(fp, "%s,%s\n", (*videos[i]).title, (*videos[i]).url);
  }

  fclose(fp);
}

int main() {
  // Initialize CURL
  CURL *curl = curl_easy_init();
  if (curl == NULL) {
    printf("Error initializing CURL\n");
    return 1;
  }

  // Set the URL to crawl
  curl_easy_setopt(curl, CURLOPT_URL, "https://www.youtube.com/");

  // Declare the curl_write() function
  int curl_write(char *ptr, size_t size, size_t nmemb, void *userdata) {
    // Write the data to the videos array
    struct video *video = (struct video *)userdata;
    video->title = realloc(video->title, size * nmemb + 1);
    memcpy(video->title, ptr, size * nmemb);
    video->title[size * nmemb] = '\0';

    return size * nmemb;
  }

  // Set the callback function to handle the response
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write);

  // Set the context pointer for the callback function
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &videos);

  // Perform the request
  CURLcode res = curl_easy_perform(curl);
  if (res != CURLE_OK) {
    printf("Error performing curl request: %s\n", curl_easy_strerror(res));
    return 1;
  }

  // Clean up CURL
  curl_easy_cleanup(curl);

  // Sort the videos alphabetically
  qsort(videos, num_videos, sizeof(struct video), (int (*)(const void *, const void *))strcmp);

  // Save the videos to a CSV file
  save_videos_to_csv("videos.csv");

  // Free the videos array
  for (int i = 0; i < num_videos; i++) {
    free(videos[i]->title);
    free(videos[i]->url);
    free(videos[i]);
  }

  return 0;
}
