package org.micromanager.data;

import java.awt.Color;

import org.json.JSONException;
import org.json.JSONObject;

import org.micromanager.api.data.SummaryMetadata;
import org.micromanager.api.MultiStagePosition;

import org.micromanager.utils.ReportingUtils;

public class DefaultSummaryMetadata implements SummaryMetadata {

   public static class Builder implements SummaryMetadata.SummaryMetadataBuilder {

      private String acquisitionName_ = null;
      private String fileName_ = null;
      private String prefix_ = null;
      private String userName_ = null;
      private String microManagerVersion_ = null;
      private String metadataVersion_ = null;
      private String computerName_ = null;
      private String directory_ = null;
      
      private Double waitInterval_ = null;
      private Double[] customIntervalsMs_ = null;
      private String startDate_ = null;
      private Integer numComponents_ = null;
      private MultiStagePosition[] stagePositions_ = null;

      @Override
      public DefaultSummaryMetadata build() {
         return new DefaultSummaryMetadata(this);
      }
      
      @Override
      public SummaryMetadataBuilder acquisitionName(String name) {
         acquisitionName_ = name;
         return this;
      }

      @Override
      public SummaryMetadataBuilder fileName(String fileName) {
         fileName_ = fileName;
         return this;
      }

      @Override
      public SummaryMetadataBuilder prefix(String prefix) {
         prefix_ = prefix;
         return this;
      }

      @Override
      public SummaryMetadataBuilder userName(String userName) {
         userName_ = userName;
         return this;
      }

      @Override
      public SummaryMetadataBuilder microManagerVersion(String microManagerVersion) {
         microManagerVersion_ = microManagerVersion;
         return this;
      }

      @Override
      public SummaryMetadataBuilder metadataVersion(String metadataVersion) {
         metadataVersion_ = metadataVersion;
         return this;
      }

      @Override
      public SummaryMetadataBuilder computerName(String computerName) {
         computerName_ = computerName;
         return this;
      }

      @Override
      public SummaryMetadataBuilder directory(String directory) {
         directory_ = directory;
         return this;
      }

      @Override
      public SummaryMetadataBuilder waitInterval(Double waitInterval) {
         waitInterval_ = waitInterval;
         return this;
      }

      @Override
      public SummaryMetadataBuilder customIntervalsMs(Double[] customIntervalsMs) {
         customIntervalsMs_ = customIntervalsMs;
         return this;
      }

      @Override
      public SummaryMetadataBuilder startDate(String startDate) {
         startDate_ = startDate;
         return this;
      }

      @Override
      public SummaryMetadataBuilder numComponents(Integer numComponents) {
         numComponents_ = numComponents;
         return this;
      }

      @Override
      public SummaryMetadataBuilder stagePositions(MultiStagePosition[] stagePositions) {
         stagePositions_ = stagePositions;
         return this;
      }
   }
   
   private String acquisitionName_ = null;
   private String fileName_ = null;
   private String prefix_ = null;
   private String userName_ = null;
   private String microManagerVersion_ = null;
   private String metadataVersion_ = null;
   private String computerName_ = null;
   private String directory_ = null;
   
   private Double waitInterval_ = null;
   private Double[] customIntervalsMs_ = null;
   private String startDate_ = null;
   private Integer numComponents_ = null;
   private MultiStagePosition[] stagePositions_ = null;

   public DefaultSummaryMetadata(Builder builder) {
      acquisitionName_ = builder.acquisitionName_;
      fileName_ = builder.fileName_;
      prefix_ = builder.prefix_;
      userName_ = builder.userName_;
      microManagerVersion_ = builder.microManagerVersion_;
      metadataVersion_ = builder.metadataVersion_;
      computerName_ = builder.computerName_;
      directory_ = builder.directory_;
      
      waitInterval_ = builder.waitInterval_;
      customIntervalsMs_ = builder.customIntervalsMs_;
      startDate_ = builder.startDate_;
      numComponents_ = builder.numComponents_;
      stagePositions_ = builder.stagePositions_;
   }

   @Override
   public String getAcquisitionName() {
      return acquisitionName_;
   }

   @Override
   public String getFileName() {
      return fileName_;
   }

   @Override
   public String getPrefix() {
      return prefix_;
   }

   @Override
   public String getUserName() {
      return userName_;
   }

   @Override
   public String getMicroManagerVersion() {
      return microManagerVersion_;
   }

   @Override
   public String getMetadataVersion() {
      return metadataVersion_;
   }

   @Override
   public String getComputerName() {
      return computerName_;
   }

   @Override
   public String getDirectory() {
      return directory_;
   }

   @Override
   public Double getWaitInterval() {
      return waitInterval_;
   }

   @Override
   public Double[] getCustomIntervalsMs() {
      return customIntervalsMs_.clone();
   }

   @Override
   public String getStartDate() {
      return startDate_;
   }

   @Override
   public Integer getNumComponents() {
      return numComponents_;
   }

   @Override
   public MultiStagePosition[] getStagePositions() {
      return stagePositions_.clone();
   }

   @Override
   public SummaryMetadataBuilder copy() {
      return new Builder()
            .acquisitionName(acquisitionName_)
            .fileName(fileName_)
            .prefix(prefix_)
            .userName(userName_)
            .microManagerVersion(microManagerVersion_)
            .metadataVersion(metadataVersion_)
            .computerName(computerName_)
            .directory(directory_)
            .waitInterval(waitInterval_)
            .customIntervalsMs(customIntervalsMs_)
            .startDate(startDate_)
            .numComponents(numComponents_)
            .stagePositions(stagePositions_);
   }

   /**
    * For temporary backwards compatibility, generate a new SummaryMetadata
    * from a provided JSON object.
    */
   public static SummaryMetadata legacyFromJSON(JSONObject tags) {
      if (tags == null) {
         return new Builder().build();
      }
      // Most of these fields are not exposed in MDUtils and thus are 
      // functionally read-only from the perspective of the Java layer, 
      // excepting the acquisition engine (which is presumably what sets them
      // in the first place).
      // TODO: not preserving the position-related metadata.
      Builder builder = new Builder();
      try {
         builder.acquisitionName(tags.getString("Name"));
      }
      catch (JSONException e) {
         ReportingUtils.logError("Failed to set field acquisitionName");
      }

      try {
         builder.prefix(tags.getString("Prefix"));
      }
      catch (JSONException e) {
         ReportingUtils.logError("Failed to set field prefix");
      }

      try {
         builder.userName(tags.getString("UserName"));
      }
      catch (JSONException e) {
         ReportingUtils.logError("Failed to set field userName");
      }

      try {
         builder.microManagerVersion(tags.getString("MicroManagerVersion"));
      }
      catch (JSONException e) {
         ReportingUtils.logError("Failed to set field microManagerVersion");
      }

      try {
         builder.metadataVersion(tags.getString("MetadataVersion"));
      }
      catch (JSONException e) {
         ReportingUtils.logError("Failed to set field metadataVersion");
      }

      try {
         builder.computerName(tags.getString("ComputerName"));
      }
      catch (JSONException e) {
         ReportingUtils.logError("Failed to set field computerName");
      }

      try {
         builder.directory(tags.getString("Directory"));
      }
      catch (JSONException e) {
         ReportingUtils.logError("Failed to set field directory");
      }

      try {
         builder.waitInterval(tags.getDouble("WaitInterval"));
      }
      catch (JSONException e) {
         ReportingUtils.logError("Failed to set field waitInterval");
      }

      try {
         builder.customIntervalsMs(new Double[] {Double.parseDouble(tags.getString("CustomIntervals_ms"))});
      }
      catch (JSONException e) {
         ReportingUtils.logError("Failed to set field customIntervalsMs(new Double[] {Double.parseDouble");
      }

      try {
         builder.startDate(tags.getString("StartTime"));
      }
      catch (JSONException e) {
         ReportingUtils.logError("Failed to set field startDate");
      }

      try {
         builder.numComponents(tags.getInt("NumComponents"));
      }
      catch (JSONException e) {
         ReportingUtils.logError("Failed to set field numComponents");
      }
      return builder.build();
   }

   /**
    * For backwards compatibility, convert to a JSON representation.
    */
   @Override
   public JSONObject legacyToJSON() {
      try {
         JSONObject result = new JSONObject();
         result.put("FileName", fileName_);
         result.put("Name", acquisitionName_);
         result.put("Prefix", prefix_);
         result.put("UserName", userName_);
         result.put("MicroManagerVersion", microManagerVersion_);
         result.put("MetadataVersion", metadataVersion_);
         result.put("ComputerName", computerName_);
         result.put("Directory", directory_);
         result.put("WaitInterval", waitInterval_);
         result.put("CustomIntervals_ms", customIntervalsMs_);
         result.put("StartTime", startDate_);
         result.put("NumComponents", numComponents_);
         result.put("Positions", stagePositions_);
         return result;
      }
      catch (JSONException e) {
         ReportingUtils.logError(e, "Couldn't convert DefaultSummaryMetadata to JSON");
         return null;
      }
   }
}
