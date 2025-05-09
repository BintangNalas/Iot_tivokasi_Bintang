<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

return new class extends Migration
{
    /**
     * Run the migrations.
     */
    public function up(): void
    {
        Schema::create('transaksi_sensor', function (Blueprint $table) {
            $table->id('id')->startingValue(1);
            $table->string('nama_sensor', 255);
            $table->integer('nilai1', false)->length(255);
            $table->integer('nilai2', false)->length(255);
            $table->timestamps();
        });
    }

    /**
     * Reverse the migrations.
     */
    public function down(): void
    {
        Schema::dropIfExists('transaksi_sensor');
    }
};
